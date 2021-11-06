
/*
 * File: Main_Proto
 * Description: Used during the prototype phase to test getting data from strain gauge
 * Date: 2021-11-03
 * Author: Andy Keats (axk7655@rit.edu)
 * 
 */

#include "HX711.h"

#define cal_factor 0

#define DOUT  3
#define CLK  2

HX711 scale;
 
void setup() {
    Serial.begin(115200);               //initial the Serial
    pinMode(A3, INPUT);

    scale.begin(DOUT, CLK);
    scale.set_scale(cal_factor);
    scale.tare();
}
 
void loop()
{
  if(Serial.available())
  {
    Serial.print(scale.get_units(), 1); // Gets from amp and ADC board
   
    Serial.write(analogRead(A3));    //send onboard ADC value over bluetooth
    Serial.print(analogRead(A3));    //To the terminal
    Serial.write("\n");
  }
}  
