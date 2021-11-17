#include "HX711.h"

#define calibration_factor 0.0 //-7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define offset_factor 0.0

#define DOUT  5
#define CLK  4

HX711 scale;

void setup() {
    Serial.begin(115200);               //initial the Serial

    scale.begin(DOUT, CLK);
    scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
    scale.set_offset(offset_factor); 
    //scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

    Serial.println("Setup done.");

    long int t1 = 0;
    long int t2 = 0;
    int idx = 0;
    int data = 0;
    
}
 
void loop()
{
  int idx = 0;
    if(Serial.available())
    {
        int data = scale.read();
        //Serial.write(data);    //send over BLE 
        Serial.println(data); //send over serial
        //Serial.write(idx);
        idx = idx + 1;
        
    }
} 
