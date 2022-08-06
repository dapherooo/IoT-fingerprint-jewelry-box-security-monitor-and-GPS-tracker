#include <TinyGPS++.h> 
#define BLYNK_PRINT Serial
#define BLYNK_HEARTBEAT 30
#include <WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleEsp32.h> 

// Variables for storing GPS Data
float latitude;
float longitude;
float speed;
float satellites;
String direction;

//static const int RXPin = 27, TXPin = 14;
static const uint32_t GPSBaud = 9600;

char auth[] = "2jkuXfLvPRj-7YSHp9I3Qw6ZhmN3Xqgt";   
char ssid[] = "POJOK SENJA"; 
char pass[] = "ciumdulu";


TinyGPSPlus gps;
//SoftwareSerial ss(RXPin, TXPin);

WidgetMap myMap(V0);
BlynkTimer timer;

unsigned int move_index = 1;

void setup()
{
  // Set console baud rate
  Serial.begin(9600);
  delay(10);
  Serial1.begin(9600, SERIAL_8N1, 14, 27);
  //ss.begin(GPSBaud);
  //Serial.println(TinyGPSPlus::libraryVersion());
  Blynk.begin(auth, ssid, pass,"blynk-cloud.com",8080);

}

void loop()
{
  while(Serial1.available() > 0)
    if (gps.encode(Serial1.read()))
        displayInfo();
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
      Blynk.run();
      timer.run();
}

void displayInfo()
{
  if (gps.location.isValid())
  {
//    Serial.println(gps.location.lat(), 6);
//    Serial.println(gps.location.lng(), 6);
    
    latitude = (gps.location.lat());     //Storing the Lat. and Lon.
    longitude = (gps.location.lng());

   // Serial.print("LAT:  ");
   // Serial.println(latitude, 6);  // float to x decimal places
   // Serial.print("LONG: ");
   // Serial.println(longitude, 6);
    Blynk.virtualWrite(V1, String(latitude, 6));
    Blynk.virtualWrite(V2, String(longitude, 6));
    
    myMap.location(move_index, latitude, longitude, "GPS_Location");
    
    speed = gps.speed.kmph();               //get speed
    Blynk.virtualWrite(V3, speed);

    direction = TinyGPSPlus::cardinal(gps.course.value()); // get the direction
    Blynk.virtualWrite(V4, direction);
    
    satellites = gps.satellites.value();    //get number of satellites
    Blynk.virtualWrite(V5, satellites);
  }
  else
  {
    Serial.println(F("INVALID"));
  }
  
}
