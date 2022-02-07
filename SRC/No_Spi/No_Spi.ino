const int pinSCK = 9;  // clock digital out
const int pinDAT = 8;  // ready/data digital input
//const int pinPwrDn = 10; // power down/reset digital out

long count; // ADC result
const unsigned long waitMs = 600000; // delay btwn reads
unsigned long nowMs;
unsigned long prevMs=0;

// for weight statistics
float countF;
float wtSum=0.0;
float numReads=0.0;

void setup() { 
  Serial.begin(250000);
  Serial.println(F("ADC 24-bit test; zero diff 524288; stat B01000001")); 

  //*** ADC setup
  pinMode(pinDAT,INPUT_PULLUP); // pull high (when shut down, ADC tri-states pin)

  pinMode(pinSCK,OUTPUT);     
  digitalWrite(pinSCK,HIGH);  // start high (and end high); is active going low  
}

void loop() {
 
  nowMs = millis();
//  chkButtons();     // check LCD buttons and change backlight or show free RAM

  if((nowMs - prevMs > waitMs)) {
    prevMs = nowMs;


    readADC();      // get ADC count
    doCalcs();      // do max, min, sum (for avg)
    PrintSerial();  // show on computer, if connected
  }
}

void readADC() {
  byte i;
  byte statusBits = 0; // ADC status bits 
  byte numTry = 0;     // number of attempts to read ADC
  count = 0;  
  numReads += 1;       // number of calls to read ADC (used to calc averages)

  while(statusBits ^ B01001101) { 
    // if statusBits doesn't match that pattern
    // then the ADC has reported an error in conversion or in the read
    // and XOR will return non-zero (i.e., true), and loop will continue.
    // If statusBits matches that pattern, 
    // then XOR will return zero (false) and loop will end.

    while(digitalRead(pinDAT));  // goes low when data is ready

    // then get 24 bits, MSB first
    for(i=0;i<24;i++)
    { 
      count=count<<1;             // shift in a zero; 1st time thru just shifts all zeros
      digitalWrite(pinSCK, LOW);  // Clock was initialized high; is active going low (here)
      if(digitalRead(pinDAT))     // read a bit and add one to count if bit is high
        count++;
      digitalWrite(pinSCK, HIGH); // inactive going high
    }
      count=count&0xFFFFFF; // mask, if you don't want LSB digits, there all are used

    // get the 8 status bits
    for(i=0;i<8;i++)
    { 
      statusBits=statusBits<<1;
      digitalWrite(pinSCK, LOW);
      if(digitalRead(pinDAT))
        statusBits++;    
      digitalWrite(pinSCK, HIGH);
    }       

    numTry += 1;              // count number of attempts
    if (numTry >= 10) {       // if ten, then
      statusBits = B01000001; // force a return, with a number
    }
  }
}

void doCalcs() {

  countF = (count - 8388608); 
  countF = countF * 0.000000596046448;
   wtSum += countF;
   if(numReads>3){numReads=1;wtSum=countF;}
}

void PrintSerial() {

  // print to computer, if connected
  Serial.println(F("**********"));
  Serial.print("i=");
  Serial.println(numReads);     
  Serial.print("count=");
  Serial.println(countF,3);
  Serial.print("sum=");
  Serial.println(wtSum/numReads);      
}
