#include <Arduino.h>
#include <LoRa.h>

#define BAND 868E6 // you can set band here directly,e.g. 868E6,915E6
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

constexpr size_t const RADIOHEAD_HDR_SIZE = 4;

void setup()
{
  Serial.begin(115200);
  SPI.begin();
  LoRa.setPins(RFM95_CS, RFM95_RST, RFM95_INT);
  if (!LoRa.begin(BAND))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  LoRa.enableCrc();
  LoRa.setSpreadingFactor(7);
  LoRa.setPreambleLength(8);
  LoRa.setSignalBandwidth(125000);
  LoRa.setCodingRate4(5);
}

void loop()
{
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  size_t cnt = 0;
  if (packetSize)
  {
    // received a packet
    Serial.print("Received packet '");
    // read packet
    while (LoRa.available())
    {
      char c = LoRa.read();
      if (cnt > RADIOHEAD_HDR_SIZE - 1)
      {
        Serial.print(c);
      }
      cnt++;
    }
    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
