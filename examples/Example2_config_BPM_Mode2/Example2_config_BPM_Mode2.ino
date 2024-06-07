/*
 A summary of the hardware connections are as follows: 
 SDA -> SDA
 SCL -> SCL
 RESET -> PIN 4
 MFIO -> PIN 5

 Author: Elias Santistevan
 Date: 8/2019
 SparkFun Electronics

 If you run into an error code check the following table to help diagnose your problem: 
 1 = Unavailable Command
 2 = Unavailable Function
 3 = Data Format Error
 4 = Input Value Error
 5 = Try Again
 255 = Error Unknown
*/
#include <SparkFun_Bio_Sensor_Hub_Library.h>
#include <Wire.h>

int resPin = 4;
int mfioPin = 5;
SparkFun_Bio_Sensor_Hub bioHub(resPin, mfioPin); 
bioData body;  
void setup()
{
  Serial.begin(115200);
  Wire.begin();
  int result = bioHub.begin();
  if (result == 0)
  {
    Serial.println("Sensor started!");
  }
  else
  {  
    Serial.println("Could not communicate with the sensor!");
  }
  Serial.println("Configuring Sensor...."); 
  int error = bioHub.configBpm(MODE_TWO); // Configuring just the BPM settings. 
  if(error == 0){ // Zero errors
    Serial.println("Sensor configured.");
  }
  else 
  {
    Serial.println("Error configuring sensor.");
    Serial.print("Error: "); 
    Serial.println(error); 
  }
  Serial.println("Loading up the buffer with data....");
  delay(4000); 
}
void loop()
{
    body = bioHub.readBpm();
    if(body.heartrate==0 || body.oxygen==0)
    {
       Serial.println("Sensor is reading the data");
       goto L1;
    }
    Serial.print("Heartrate: ");
    Serial.println(body.heartRate);
    Serial.print("Oxygen: ");
    Serial.println(body.oxygen);
    L1:
    delay(700); 
}
