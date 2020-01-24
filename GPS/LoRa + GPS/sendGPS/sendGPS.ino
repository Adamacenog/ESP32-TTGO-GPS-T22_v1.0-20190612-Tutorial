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
 * Made by AdamacenoG:
 * https://github.com/Adamacenog/ESP32-TTGO-GPS-T22_v1.0-20190612-Tutorial
 * 
 */

#include <TinyGPS++.h>
#include <axp20x.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)

/*
 * Band frequencies: 
 * 433 Hz - 433E6 
 * 868 Hz - 868E6 
 * 915 Hz - 915E6
 */
 
#define BAND    868E6

String gpsMsg;
double lat = 0.0, lng = 0.0;
int i = 0;

TinyGPSPlus gps;
HardwareSerial GPS(1);
AXP20X_Class axp;


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

  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //LoRa.onReceive(cbk);
  //LoRa.receive();
  Serial.println("init ok");
  delay(1500);
  Serial.print("Starting GPS, this might take a while (~ 5 min max)");
}

void loop()
{
  unsigned long start = millis();

  lat = gps.location.lat();
  lng = gps.location.lng();

  if (lat == 0.0 || lng == 0.0){
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
    gpsMsg = "[";
    gpsMsg += String(lng,6);
    gpsMsg += ",";
    gpsMsg += String(lat,6);
    gpsMsg += "],";
    
    Serial.println(gpsMsg);
  
    LoRa.beginPacket();
    LoRa.print(gpsMsg);
    LoRa.endPacket();
  }

  do
  {
    while (GPS.available())
      gps.encode(GPS.read());
  } while (millis() - start < 1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}
