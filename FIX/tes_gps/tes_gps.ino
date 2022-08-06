#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 14, TXPin = 27;
static const uint32_t GPSBaud = 9600;
float latitude;
float longitude;
// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
//ss.begin(9600, SERIAL_8N1, 4, 3);
  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
}
void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while ( ss.available() > 0)
    if (gps.encode( ss.read()))
      displayInfo();
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}
void displayInfo()
{
  if (gps.location.isValid())
  {
//    Serial.println(gps.location.lat(), 6);
//    Serial.println(gps.location.lng(), 6);
    
    latitude = (gps.location.lat());     //Storing the Lat. and Lon.
    longitude = (gps.location.lng());

    Serial.print("LAT:  ");
    Serial.println(latitude, 6);  // float to x decimal places
    Serial.print("LONG: ");
    Serial.println(longitude, 6);
   // Blynk.virtualWrite(V1, String(latitude, 6));
   // Blynk.virtualWrite(V2, String(longitude, 6));
    
   // myMap.location(move_index, latitude, longitude, "GPS_Location");
    
   // speed = gps.speed.kmph();               //get speed
  //  Blynk.virtualWrite(V3, speed);

   // direction = TinyGPSPlus::cardinal(gps.course.value()); // get the direction
   // Blynk.virtualWrite(V4, direction);
    
   // satellites = gps.satellites.value();    //get number of satellites
   // Blynk.virtualWrite(V5, satellites);
  }
  else
  {
    Serial.println(F("INVALID"));
  }
}
