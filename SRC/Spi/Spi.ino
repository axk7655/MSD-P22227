#include <SPI.h>

  long spia;
  long spib;
  long spic;
  float countF;
  unsigned long spie=0;

void setup (void) {

  Serial.begin(9600);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);  // 1 MHz
  SPI.setBitOrder(MSBFIRST); 
  SPI.setDataMode(SPI_MODE3);       //CPOL=1 the base value of the clock is one
                                    //CPHA=1 data are captured on clock's rising edge 
                  //and data are propagated on a falling edge.
}


void loop() {
  while(digitalRead(12)==HIGH);       // MISO          

  spia=SPI.transfer(0);                   //byte
  spib=SPI.transfer(0);                   //byte                   
  spic=SPI.transfer(0);                   //byte 

  spie = spia<<16 | spib<<8 | spic ;
  if (spie < 0){spie = 0;}
  countF = (spie-8387550);
// Serial.print (value);
  countF = countF * 0.000000596046448 ;   //one step in voltage
  

  Serial.print (spia, HEX);  
  Serial.print (spib, HEX);  
  Serial.println (spic, HEX); 
  Serial.println (spie, HEX);   
  Serial.println (countF,3);
  while(digitalRead(12)==LOW);
  {
  }
}
