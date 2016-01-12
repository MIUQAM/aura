#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

#define PIN 6
#define LED_COUNT 490
#define UDP_TX_PACKET_MAX_SIZE 1522

byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x55 };
IPAddress ip(10, 0, 1, 155);

unsigned int localPort = 9155;      // local port to listen on
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  
  strip.setBrightness(127);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
//  Serial.begin(115200);
//  Serial.println("Init...");
}

void loop() {
  //pinMode(pwPin, INPUT);
  
  //pulse = pulseIn(pwPin, HIGH);
  
  //inches = pulse/147;
  
  int packetSize = Udp.parsePacket();
  int colorPacket = 0;
  if(packetSize)
  {
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
  }
//  Serial.println("OK");
//  Serial.println(packetBuffer);
  for(uint16_t j = 0; j < LED_COUNT; j++) {
//    if(j > 200)
//      Serial.println(j);
    //leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB(packetBuffer[(j*3)],packetBuffer[(j*3)+1],packetBuffer[(j*3)+2]);
//    uint16_t color = packetBuffer[(j*3)] + (packetBuffer[(j*3)+1] << 8) + (packetBuffer[(j*3)+2] << 16);
//    uint32_t color = packetBuffer[(j*3)] + (packetBuffer[(j*3)+1] << 8) + (packetBuffer[(j*3)+2] << 16);
    strip.setPixelColor(j, strip.Color(packetBuffer[(j*3)], packetBuffer[(j*3)+1], packetBuffer[(j*3)+2]));
  }
  strip.show();
}

//void ledPacket

void ledBinary(char str[]) {
  char sup[9];
//  Serial.println(sizeof(packetBuffer));
  for(uint16_t i = 0; i < LED_COUNT; i++) {
    for(byte j = 0; j < 8; j++) {
      sup[j] = packetBuffer[j + (i * 8)];
      //packetBuffer[j] = packetBuffer[i * 8];
    }
    sup[8] = '\0';
    //Serial.print(atol(sup));
    //sup[8] = '\0';
    //Serial.print(atoi(sup));
    strip.setPixelColor(i, atol(sup));
    //memcpy(packetBuffer,packetBuffer, (50 * 8) - (i * 8));
  }
}

void lightLed(int ledPos, uint32_t c) {
  strip.setPixelColor(ledPos, c);
  strip.show();
}

void breathStrip(uint32_t c, uint8_t wait) {
  //Start inhale
  for(int j = 0; j < 255; j++) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0 + j));
      }
    strip.show();
  }
  //Start exhale
  for(int j = 0; j < 255; j++) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 255 - j));
      }
    strip.show();
  }
}
