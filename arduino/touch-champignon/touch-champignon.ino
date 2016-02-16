#include "mpr121.h"
#include "i2c.h"

#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0x40 };
IPAddress ip(10, 0, 1, 140);
IPAddress destinationIP(10, 0, 1, 255);
unsigned int destinationPort = 9140;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

unsigned int listeningPort = 8514;      // local port to listen on
unsigned int sendValPort = 8614;      // local port to listen on

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

boolean verbose = false;
int numberOfTouch = 2;
byte sensitivity = 20;
uint16_t tresh1;
uint16_t tresh2;
uint16_t tresh3;
unsigned long lastExecution;
int timeBetweenExecutions = 1000;

void setup()
{
  //configure serial out
  Serial.begin(115200);
  
  // initalize I2C bus. Wiring lib not used. 
  i2cInit();
  
  // initialize mpr121
  mpr121QuickConfig();
  Serial.println("Initializing...");
  delay(500);
  Serial.println("DONE!");
  Ethernet.begin(mac,ip);
  Udp.begin(listeningPort);
  tresh1 = getSensorMeasurement(0) - sensitivity; //Fake sensor, the first one never works
  tresh1 = getSensorMeasurement(0) - sensitivity;
  Serial.print("t1: ");
  Serial.print(tresh1);
  delay(500);
  tresh2 = getSensorMeasurement(1) - sensitivity;
  Serial.print(" t2: ");
  Serial.print(tresh2);
  delay(500);
  tresh3 = getSensorMeasurement(2) - sensitivity;
  Serial.print(" t3: ");
  Serial.print(tresh3);
  
//  t.every(5000, sendReading); //Function to send and saveState
  lastExecution = millis();
  Serial.println("");
  delay(2000);
}

void loop()
{
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    // Read each command pair 
    char* currentSens = strtok(packetBuffer, " ");
    byte currentVar = 0;
    while (currentSens != 0)
    {
      if(currentVar == 0)
        tresh1 = atoi(currentSens);
      if(currentVar == 1)
        tresh2 = atoi(currentSens);
//    Serial.println(currentSens);

    // Find the next command in input string
    currentVar++;
    currentSens = strtok(0, " ");
    }
  }
  
  uint16_t value1 = getSensorMeasurement(0);
  uint16_t value2 = getSensorMeasurement(1);
  uint16_t value3 = getSensorMeasurement(2);
  uint16_t value4 = getSensorMeasurement(3);
  byte touched1 = 0;
  byte touched2 = 0;
  byte touched3 = 0;
  byte touched4 = 0;

  if(value1 < tresh1)
    touched1 = 1;
  if(value2 < tresh2)
    touched2 = 2;
  if(value3 < tresh3)
    touched3 = 4;
  if(value4 < 520)
    touched4 = 8;
//  Serial.println("1 : " + String(touched1));
//  Serial.println("2 : " + String(touched4));
//  Serial.println("Touched2 : " + touched2);
//  Serial.println("Touched3 : " + touched3);
//  Serial.println("Touched4 : " + touched4);
  int valTot = touched1 + touched2 + touched3;
  int mask = pow(2, numberOfTouch);
  byte touchData = valTot & mask;

  if(verbose) {
    Serial.print("1: ");
    Serial.print(value1);
    Serial.print(" t1: ");
    Serial.print(tresh1);
    Serial.print(" 2: ");
    Serial.print(value2);
    Serial.print(" t2: ");
    Serial.print(tresh2);
    Serial.print(" 3: ");
    Serial.print(value3);
    Serial.print(" t3: ");
    Serial.print(tresh3);
    Serial.println("");
//    Serial.print("4: ");
//    Serial.println(value4);
  }
//  Serial.println(touchData);
  Udp.beginPacket(destinationIP, destinationPort);
  Udp.print(touchData);
  Udp.endPacket();
//  delay(100);
//  Serial.println("tabarnac");
  if(millis() > timeBetweenExecutions + lastExecution)
    sendReading();
}

void sendReading() {
  lastExecution = millis();
  uint16_t value1 = getSensorMeasurement(0);
  uint16_t value2 = getSensorMeasurement(1);
  Udp.beginPacket(destinationIP, sendValPort);
  Udp.print(value1);
  Udp.print(" ");
  Udp.print(tresh1);
  Udp.print(" ");
  Udp.print(value2);
  Udp.print(" ");
  Udp.print(tresh2);
  Udp.endPacket();
}

int getSensorMeasurement(byte sensorNumber)
{
  int value = mpr121Read2Bytes(0x04 + (sensorNumber << 1));  
  return value;
}

void mpr121QuickConfig(void)
{
  // reset (in case already running)
  mpr121Write(0x80, 0x63);

  // auto config off  
  mpr121Write(ATO_CFG0, 0x00);
  
  // big sensors, use max charge current
  // FFI = 00 (default)
  // CDC = 111111
  mpr121Write(0x5C, 0x3F);

  // CDT=011 charge time, use the one that fits the size of your sensor best
  // SFI=00 (default)
  // ESI=100 (default)
  mpr121Write(0x5D, 0x24); // CDT=001
  //mpr121Write(0x5D, 0x44); // CDT=010
  //mpr121Write(0x5D, 0x64); // CDT=011
  //mpr121Write(0x5D, 0x84); // CDT=100
  
  // Electrode Configuration
  mpr121Write(ELE_CFG, 0x0C);	// Enables all 12 Electrodes
//  mpr121Write(ELE_CFG, 0x01);  // Enable first electrode only
}
