/*
 * 
 * Original code: https://github.com/LilyGO/TTGO-T-Beam
 * Modified by AdamacenoG & lucascamposj:
 * https://github.com/Adamacenog/ESP32-TTGO-GPS-T22_v1.0-20190612-Tutorial
 * 
 */

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

unsigned int counter = 0;

String rssi = "RSSI --";
String packSize = "--";
String packet ;
String msg = "";

void setup() {  
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Sender Test");
  
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("init ok");
  delay(1500);
}

void loop() {

  if(Serial.available() > 0){
    msg = Serial.readString();
    // send packet
    msg = "("+String(counter)+"): "+ msg;
    Serial.print(msg);
    
    LoRa.beginPacket();
    LoRa.print(msg);
    LoRa.endPacket();
    counter++;
  }
}
