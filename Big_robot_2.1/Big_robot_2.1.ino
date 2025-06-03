#define LED_COUNT 92       // число светодиодов в кольце/ленте //146
#define BOTTOM_INDEX 10    // светодиод начала отсчёта
#define LED_DT 2           // пин, куда подключен DIN ленты
#define max_bright 50      // максимальная яркость (0 - 255)
#define T_SPEED 25         // скорость движения (время между сменой положения)
#define NUM_LED 10         // количество светодиодов, которые будут гореть
#define NUM 3              // количество бегущий линий

int br = 255;     // яркость светодиодов в эффекте
int n;            // номер светодиода, который надо включить
int n1;           // номер светодиода, который надо выключить
int k1;

#include <FastLED.h>
CRGB leds[LED_COUNT];

void setup() {
  FastLED.addLeds<WS2812, LED_DT, GRB>(leds, LED_COUNT);
  FastLED.setBrightness(max_bright);
  Serial.begin(9600);
}

void loop() {
  for (int k = BOTTOM_INDEX; k < LED_COUNT; k++) {
    k1 = k;
    for (int i1 = 0; i1 < NUM; i1++) {
      br = 255;
      for (int i = 0; i < NUM_LED + 1; i++) {
        if (k1 - i < 10) {
          n = LED_COUNT - abs((k1 - BOTTOM_INDEX) - i);
        }
        else {
          n = k1 - i;
        }
        leds[n] = CHSV(150, 255, br);
        if (NUM_LED <= 5) {
          br = br - 255 / NUM_LED;
        }
        else {
          br = br - 255 / (NUM_LED + 1);
        }
      }
      if (k1 - (LED_COUNT - BOTTOM_INDEX) / NUM < 10) {
        k1 = LED_COUNT - abs(k1 - ((LED_COUNT - BOTTOM_INDEX) / NUM + BOTTOM_INDEX));
      }
      else {
        k1 = k1 - (LED_COUNT - BOTTOM_INDEX) / NUM;
      }
    }
    FastLED.show();
    delay(T_SPEED);
  }
}
