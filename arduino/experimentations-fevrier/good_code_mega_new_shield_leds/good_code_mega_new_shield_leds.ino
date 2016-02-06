#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

#define PIN 0
#define PIN2 1
#define PIN3 2
#define LED_COUNT 350
#define UDP_TX_PACKET_MAX_SIZE 1522

byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0x31 };
IPAddress ip(10, 0, 1, 131);

unsigned int localPort = 9131;      // local port to listen on
unsigned int localPort2 = 9132;      // local port to listen on
unsigned int localPort3 = 9153;      // local port to listen on
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char packetBuffer2[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char packetBuffer3[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;
EthernetUDP Udp2;
EthernetUDP Udp3;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(LED_COUNT, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(LED_COUNT, PIN3, NEO_GRB + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  
  strip.setBrightness(127);
  strip2.setBrightness(127);
  strip3.setBrightness(127);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip2.begin();
  strip2.show(); // Initialize all pixels to 'off'
  strip3.begin();
  strip3.show(); // Initialize all pixels to 'off'

//  rainbow(20);
  
  
  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
  Udp2.begin(localPort2);
  Udp3.begin(localPort3);
//  Serial.begin(115200);
//  Serial.println("Init...");
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
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
  int packetSize2 = Udp2.parsePacket();
  if(packetSize2)
  {
    Udp2.read(packetBuffer2,UDP_TX_PACKET_MAX_SIZE);
  }
  int packetSize3 = Udp3.parsePacket();
  if(packetSize3)
  {
    Udp3.read(packetBuffer3,UDP_TX_PACKET_MAX_SIZE);
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
    strip2.setPixelColor(j, strip2.Color(packetBuffer2[(j*3)], packetBuffer2[(j*3)+1], packetBuffer2[(j*3)+2]));
    strip3.setPixelColor(j, strip3.Color(packetBuffer3[(j*3)], packetBuffer3[(j*3)+1], packetBuffer3[(j*3)+2]));
  }
  strip.show();
  strip2.show();
  strip3.show();
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


