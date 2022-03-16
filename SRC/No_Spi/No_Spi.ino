const int pinSCK = 4;  // clock digital out
const int pinDAT = 5;  // ready/data digital input
//const int pinPwrDn = 10; // power down/reset digital out


//-------------------Calibration Numbers----------------
long offSet = 8802500;
const float scale = 0.0004;
//-------------------Calibration Numbers----------------

long count; // ADC result
const unsigned long waitMs = 600; // delay btwn reads
unsigned long nowMs;
unsigned long prevMs=0;

// for weight statistics
float countF;
float wtSum = 0.0;
float numReads = 0.0;

//control flag
//int TARE = 0;

void setup() { 
  Serial.begin(9600);
  //Serial.println(F("ADC 24-bit test; zero diff 524288; stat B01000001")); 

  //*** ADC setup
  pinMode(pinDAT,INPUT_PULLUP); // pull high (when shut down, ADC tri-states pin)

  pinMode(pinSCK,OUTPUT);     
  digitalWrite(pinSCK,HIGH);  // start high (and end high); is active going low  
}

void loop() {
  long ADCresult = 0;
  float CONVresult = 0;
  delay(5000);
  nowMs = millis();
  //Serial.print("Current MS : ");
  //Serial.println(nowMs);
//  chkButtons();     // check LCD buttons and change backlight or show free RAM

  //Serial.println("In Loop");
  if((nowMs - prevMs > waitMs)) {
    prevMs = nowMs;
    //Serial.println("In time check");

    readADC();      // get ADC count
    //CONVresult = doCalcs(ADCresult);      // do max, min, sum (for avg)
    //PrintSerial();  // show on computer, if connected
  }
}

void readADC() {
  byte i;
  byte statusBits = 0; // ADC status bits 
  byte numTry = 0;     // number of attempts to read ADC
  count = 0;  
  numReads += 1;       // number of calls to read ADC (used to calc averages)
  long result = 0;
  int TARE = 0;

  while(statusBits ^ B01001101) { 
    // if statusBits doesn't match that pattern
    // then the ADC has reported an error in conversion or in the read
    // and XOR will return non-zero (i.e., true), and loop will continue.
    // If statusBits matches that pattern, 
    // then XOR will return zero (false) and loop will end.
    //Serial.println("Passed status check, waiting on data to be ready");

    while(digitalRead(pinDAT));  // goes low when data is ready
    //Serial.println("Data reading");
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
      if (TARE == 0)
      {
        offSet = count;
        TARE = 1;
      }
      doCalcs(count);
    //Serial.print("Data = ");
    //Serial.println(count);
    // get the 8 status bits
    for(i=0;i<8;i++)
    { 
      statusBits=statusBits<<1;
      digitalWrite(pinSCK, LOW);
      if(digitalRead(pinDAT))
        statusBits++;    
      digitalWrite(pinSCK, HIGH);
    }     
    //Serial.print("Status bits = ");  
    //Serial.println(statusBits);
    numTry += 1;              // count number of attempts
    if (numTry >= 10) {       // if ten, then
      statusBits = B01000001; // force a return, with a number
    }
  }
  //.println("Failed check");
}

float doCalcs(long ADCresult) {
  //Applies offset and scaling factor
  countF = (ADCresult - offSet); 
  countF = countF * scale;
   //wtSum += countF;
   //if(numReads>3){numReads=1;wtSum=countF;}
   PrintSerial(countF); //prints over bluetooth
}

void PrintSerial(float toPrint) {
   Serial.println(toPrint);
  // print to computer, if connected
  //Serial.println(F("**********"));
  //Serial.print("i=");
  //Serial.println(numReads);     
  //Serial.print("count=");
  //Serial.println(countF,3);
  //Serial.print("sum=");
  //Serial.println(wtSum/numReads);      
}
