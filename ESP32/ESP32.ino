#include <TinyGPS++.h>
#define BLYNK_HEARTBEAT 30
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#define SerialMon Serial
#include <BlynkSimpleEsp32.h>
//#define TXPin        txd
//#define RXPin        rxd

//static const int RXPin = rxd, TXPin = txd;   // GPIO 4=D2(conneect Tx of GPS) and GPIO 5=D1(Connect Rx of GPS
static const uint32_t GPSBaud = 9600; //if Baud rate 9600 didn't work in your case then use 4800

const char *gpsStream =
  "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n"
  "$GPGGA,045104.000,3014.1985,N,09749.2873,W,1,09,1.2,211.6,M,-22.5,M,,0000*62\r\n"
  "$GPRMC,045200.000,A,3014.3820,N,09748.9514,W,36.88,65.02,030913,,,A*77\r\n"
  "$GPGGA,045201.000,3014.3864,N,09748.9411,W,1,10,1.2,200.8,M,-22.5,M,,0000*6C\r\n"
  "$GPRMC,045251.000,A,3014.4275,N,09749.0626,W,0.51,217.94,030913,,,A*7D\r\n"
  "$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F\r\n";
  
TinyGPSPlus gps; // The TinyGPS++ object
WidgetMap myMap(V0);  // V0 for virtual pin of Map Widget

//SoftwareSerial ss(4,0);  // The serial connection to the GPS device

BlynkTimer timer;
float latitude;
float longitude;
float spd;       //Variable  to store the speed
float sats;      //Variable to store no. of satellites response
String bearing;  //Variable to store orientation or direction of GPS

char auth[] = "2jkuXfLvPRj-7YSHp9I3Qw6ZhmN3Xqgt";              //Your Project authentication key
char ssid[] = "POJOK SENJA";                                   // Name of your network (HotSpot or Router name)
char pass[] = "ciumdulu";                                      // Corresponding Password

//unsigned int move_index;         // moving index, to be used later
unsigned int move_index = 1;       // fixed location for now
  

void setup()
{
  Serial.begin(9600);
  Serial.println();
 // ss.begin(GPSBaud);
  Blynk.begin(auth, ssid, pass,"blynk-cloud.com",8080);
      while (*gpsStream) 
    {
        if (gps.encode(*gpsStream++))
        displayInfo();
    }
  timer.setInterval(5000L, checkGPS); // every 5s check if GPS is connected, only really needs to be done once
}

void checkGPS(){
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
      Blynk.virtualWrite(V4, "GPS ERROR");  // Value Display widget  on V4 if GPS not detected
  }
}

void loop()
{

  Blynk.run();
  timer.run();
}

void displayInfo()
{ 
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  
//  if (gps.location.isValid() ) 
//  {    
//    float latitude = (gps.location.lat());     //Storing the Lat. and Lon. 
//    float longitude = (gps.location.lng()); 
//    
//    Serial.print("LAT:  ");
//    Serial.println(latitude, 6);  // float to x decimal places
//    Serial.print("LONG: ");
//    Serial.println(longitude, 6);
//    Blynk.virtualWrite(V1, String(latitude, 6));   
//    Blynk.virtualWrite(V2, String(longitude, 6));  
//    myMap.location(move_index, latitude, longitude, "GPS_Location");
//    spd = gps.speed.kmph();               //get speed
//       Blynk.virtualWrite(V3, spd);
//       
//       sats = gps.satellites.value();    //get number of satellites
//       Blynk.virtualWrite(V4, sats);
//
//       bearing = TinyGPSPlus::cardinal(gps.course.value()); // get the direction
//       Blynk.virtualWrite(V5, bearing);                   
  }
  
 //Serial.println();
//}
