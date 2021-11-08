int sensorPin1 = A0;  // input pin for the potentiometer
int digitalValue1 = 0;// variable to store the value coming from the sensor

//int sensorPin2 = A1;  // input pin for the potentiometer
//int digitalValue2 = 0;// variable to store the value coming from the sensor


void setup() {
  Serial.begin(9600);
}

void loop() {
  digitalValue1 = analogRead(sensorPin1);// read the value from the analog channel
  //digitalValue2 = analogRead(sensorPin2);// read the value from the analog channel
  Serial.print("digital value A0= ");
  Serial.println(digitalValue1);        //print digital value on serial monitor
  //Serial.print("digital value A1= ");
  //Serial.println(digitalValue2);        //print digital value on serial monitor
  delay(100);
}
