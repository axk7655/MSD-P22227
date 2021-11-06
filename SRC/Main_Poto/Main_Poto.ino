
/*
 * File: Main_Proto
 * Description: Used during the prototype phase to test getting data from strain gauge
 * Date: 2021-11-03
 * Author: Andy Keats (axk7655@rit.edu)
 * 
 */
void setup() {
    Serial.begin(115200);               //initial the Serial
    pinMode(A3, INPUT);
}
 
void loop()
{
  if(Serial.available())
  {
    Serial.write(analogRead(A3));    //send ADC value over bluetooth
    Serial.print(analogRead(A3);    //To the terminal
    Serial.write("\n");
  }
}  
