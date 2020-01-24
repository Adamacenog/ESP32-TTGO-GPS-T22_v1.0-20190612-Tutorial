/*****************************************
  ESP32 GPS VKEL 9600 Bds
This version is for T22_v01 20190612 board
As the power management chipset changed, it
require the axp20x library that can be found
https://github.com/lewisxhe/AXP202X_Library
You must import it as gzip in sketch submenu
in Arduino IDE
This way, it is required to power up the GPS
module, before trying to read it.

Also get TinyGPS++ library from: 
https://github.com/mikalhart/TinyGPSPlus
******************************************/

/*
 * 
 * Original code: https://github.com/LilyGO/TTGO-T-Beam
 * Modified by AdamacenoG:
 * https://github.com/Adamacenog/ESP32-TTGO-GPS-T22_v1.0-20190612-Tutorial
 * 
 */

#include <TinyGPS++.h>
#include <axp20x.h>

TinyGPSPlus gps;
HardwareSerial GPS(1);
AXP20X_Class axp;

double lat = 0.0, lng = 0.0, altitude = 0.0, kmph = 0.0;
int satellites = 0, i = 0;
bool notEnoughSatelites = false;

void setup()
{
  Serial.begin(115200);
  Wire.begin(21, 22);
  if (!axp.begin(Wire, AXP192_SLAVE_ADDRESS)) {
    Serial.println("AXP192 Begin PASS");
  } else {
    Serial.println("AXP192 Begin FAIL");
  }
  axp.setPowerOutPut(AXP192_LDO2, AXP202_ON);
  axp.setPowerOutPut(AXP192_LDO3, AXP202_ON);
  axp.setPowerOutPut(AXP192_DCDC2, AXP202_ON);
  axp.setPowerOutPut(AXP192_EXTEN, AXP202_ON);
  axp.setPowerOutPut(AXP192_DCDC1, AXP202_ON);
  GPS.begin(9600, SERIAL_8N1, 34, 12);   // 34-TX 12-RX
  Serial.print("Starting GPS, this might take a while (~ 5 min max)");
}

void loop()
{
  unsigned long start = millis();
  
  lat = gps.location.lat();
  lng = gps.location.lng();
  satellites = gps.satellites.value();
  altitude = gps.altitude.kilometers();
  kmph = gps.speed.kmph();

  notEnoughSatelites = (lat == 0.0 || lng == 0.0 || altitude == 0 || kmph == 0);

  if (satellites != 0 && notEnoughSatelites){
    Serial.print("Satellites: ");
    Serial.println(satellites);
    Serial.print("Time      : ");
    Serial.print(gps.time.hour());
    Serial.print(":");
    Serial.print(gps.time.minute());
    Serial.print(":");
    Serial.println(gps.time.second());
    Serial.println("**********************");
  }
  else if (notEnoughSatelites){
    Serial.print(".");
    i++;
    if (i%30 == 0){
      Serial.println("");
    }
    if (i == 300){
      Serial.println("5 min has passsed... try getting outside, GPS is not syncing"); 
    }
  }
  else {
    Serial.print("Latitude  : ");
    Serial.println(lat, 5);
    Serial.print("Longitude : ");
    Serial.println(lng, 5);
    Serial.print("Satellites: ");
    Serial.println(satellites);
    Serial.print("Altitude  : ");
    Serial.print(altitude);
    Serial.println("M");
    Serial.print("Time      : ");
    Serial.print(gps.time.hour());
    Serial.print(":");
    Serial.print(gps.time.minute());
    Serial.print(":");
    Serial.println(gps.time.second());
    Serial.print("Speed     : ");
    Serial.println(kmph); 
    Serial.println("**********************");
  }

  do
  {
    while (GPS.available())
      gps.encode(GPS.read());
  } while (millis() - start < 1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}
