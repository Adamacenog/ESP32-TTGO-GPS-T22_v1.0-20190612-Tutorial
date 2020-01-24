/*
 * 
 * Made by AdamacenoG & lucascamposj:
 * https://github.com/Adamacenog/ESP32-TTGO-GPS-T22_v1.0-20190612-Tutorial
 * 
 */

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <string>

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISO
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

void loraData();
void cbk(int);
void ack(int);

unsigned int counter = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;
String msg = "";
String packetMsg = "";
String sendMsg = "";
String user  = "USERNAME";

void loraData(){
  Serial.print(packet);
}

void cbk(int packetSize) {
  packet ="";
  packSize = String(packetSize,DEC);
  for (int i = 0; i < packetSize; i++) { packet += (char) LoRa.read(); }
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC) ;
  loraData();
}

void ack(int countPacket){
  LoRa.beginPacket();
  LoRa.print(countPacket);
  LoRa.endPacket();
}

void setup() {  
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Receiver Callback");
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);  
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //LoRa.onReceive(cbk);
  LoRa.receive();
  Serial.println("init ok");
  delay(1500);
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) { cbk(packetSize);  }
  delay(10);

  if(Serial.available() > 0){
    msg = Serial.readString();
    msg.remove(msg.length() - 1);
    // send packet
    packetMsg = user + "("+String(counter)+"): "+ msg + "\n";
    sendMsg = "\t\t\t\t\t\t\t\t" + msg + " :" + user + "("+String(counter)+")\n";
    Serial.print(sendMsg);
    
    LoRa.beginPacket();
    LoRa.print(packetMsg);
    LoRa.endPacket();

    counter++;
  }
}
