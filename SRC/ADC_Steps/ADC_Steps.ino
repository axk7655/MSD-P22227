//File: ADC_Steps
//Description: Takes the ADC value at 10Hz intervaul and reports over serial. 
//Author: Andy Keats
//Date: 2021-11-22


#include "HX711.h"

//---------------------------------------------------------------------------------------------------------
//Hey MECEs, Change these two only!!!
#define calibration_factor -35000.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define offset_factor 13850
//---------------------------------------------------------------------------------------------------------

#define DOUT  5
#define CLK  4

HX711 scale;

void setup() {
    Serial.begin(115200);               //initial the Serial

    scale.begin(DOUT, CLK);
    scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
    //scale.set_offset(offset_factor); 
    scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

    Serial.println("Setup done.");

    long int t1 = 0;
    long int t2 = 0;
    int idx = 0;
    int data = 0;
    
}
 
void loop()
{
  //int data = scale.read();
  //int data = scale.get_value();
  float data = scale.get_units();
  Serial.println(data, 4); //send over serial    
  //delay(100);      
} 
