#define CLK 2
#define DIO 3
#define CLK1 4
#define DT 5
#define SW 6

#define NUM_LEDS 120

#include <FastLED.h>
#include <GyverEncoder.h>
#include <GyverTM1637.h>
#include <DMXSerial.h>
#include <EEPROM.h>

#define PIN 8

GyverTM1637 disp(CLK, DIO);
Encoder enc1(CLK1, DT, SW);
CRGB leds[NUM_LEDS];

int dmx = 1;//канал dmx
int dmx1;//предыдущий канал dmx
int r;
int g;
int b;
int r1;
int g1;
int b1;
int bright = 50; // яркость LED светодиодов
int bright1;
int flag;

void setup() {
  FastLED.addLeds <WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(bright);
  disp.clear();
  disp.brightness(7);// put your setup code here, to run once:
  disp.clear();
  enc1.setType(TYPE1);
  enc1.setTickMode(AUTO);
  DMXSerial.init(DMXReceiver);
  dmx = EEPROM.read(0);
}

void loop() {
  if (flag == 0) {
    dmx1 = dmx;
    if (enc1.isPress()) {
      dmx = 1;
    }
    if (enc1.isRight()) {
      dmx++;
    }
    if (enc1.isLeft()) {
      dmx--;
    }
    if (dmx < 1) {
      dmx = 512;
    }
    if (dmx > 512) {
      dmx = 1;
    }
    if (dmx != dmx1) {
      EEPROM.update(0, dmx);
      //Serial.println(dmx);
    }
    disp.displayInt(dmx);
    r1 = r;
    g1 = g;
    b1 = b;
    bright1 = bright;
    bright = DMXSerial.read(dmx);
    r = DMXSerial.read(dmx + 1);
    g = DMXSerial.read(dmx + 2);
    b = DMXSerial.read(dmx + 3);
    if (r != r1 || g != g1 || b != b1) {
      flag = 1;
    }
    if (bright != bright1) {
      flag = 2;
    }
  }
  if (flag == 1) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(r, g, b);
      if (i == NUM_LEDS - 1) {
        flag = 0;
        FastLED.show();
      }
    }
  }
  if (flag == 2) {
    FastLED.setBrightness(bright);
    FastLED.show();
    flag = 0;
  }
}
