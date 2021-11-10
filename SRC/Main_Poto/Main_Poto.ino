
/*
 * File: Main_Proto
 * Description: Used during the prototype phase to test getting data from strain gauge
 * Date: 2021-11-03
 * Author: Andy Keats (axk7655@rit.edu)
 * 
 */

#include "HX711.h"

#define cal_factor 0

#define DOUT  5
#define CLK  4

int digitalValue = 0;

HX711 scale;
 
void setup() {
    Serial.begin(115200);               //initial the Serial
    //pinMode(A0, INPUT);                 //for ATmega ADC

    scale.begin(DOUT, CLK);             //for external ADC
    scale.set_scale(cal_factor);
    scale.tare();
}
 
void loop()
{
  //stuff that does not need the bluetooth to work
  Serial.print("Reading from ADC board: ");
  Serial.print(scale.get_units(), 1); //Reads from ADC board. 
  Serial.println(" ");
  delay(100);

  //Following only works when the bluetooth works. 
  if(Serial.available())
  {
    digitalValue = analogRead(A0);
    //Serial.write(analogRead(A0));    //send onboard ADC value over bluetooth
    Serial.println(digitalValue);    //To the terminal
    Serial.write("\n");
    delay(1000);
  }
}  
