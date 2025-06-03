#define SWITCH_MODE 2
#define MATRIX 3
#define EN_MATRIX 4
#define SOUND A0
#define BRIGHT 10 // яркость 0..15

#include <VolAnalyzer.h>
#include <GyverMAX7219.h>
#include <FastLED.h>

MAX7219 < 5, 1, MATRIX > mtrx;   // одна матрица (1х1), пин CS на D5
VolAnalyzer analyzer(SOUND);  // микрофон на А0

int x;
int x1 = 3;
int y1 = 3;
int a;
int t;
boolean flag;

void setup() {
  pinMode(EN_MATRIX, INPUT);
  pinMode(SWITCH_MODE, INPUT_PULLUP);
  mtrx.begin();       // запускаем
  mtrx.setBright(BRIGHT);  // яркость 0..15
  mtrx.clear();
  randomSeed(analogRead(A1));
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(EN_MATRIX) == 0) {
    if (digitalRead(SWITCH_MODE) == 0) {
      if (analyzer.tick()) {
        x = analyzer.getVol();
        Serial.println(x);
      }
    }
    if (digitalRead(SWITCH_MODE) == 1) {
      if (a % 10 == 0) {
        x = random(0, 100);
      }
      //mtrx.line(0, 3, 23, 3);
      //x = 0;
    }
    mtrx.clear();
    static uint16_t offs;
    offs += 20 * x / 100;
    for (uint8_t i = 0; i < 24; i++) {
      int16_t val = inoise8(i * 50, offs);
      val -= 128;
      val = val * x / 100;
      val += 128;
      val = map(val, 45, 255 - 45, 0, 7);
      mtrx.dot(i, val);
    }
    mtrx.rect(25, 1, 30, 6, GFX_FILL);
    mtrx.lineV(24, 2, 5);
    mtrx.lineV(31, 2, 5);
    mtrx.lineH(0, 26, 29);
    mtrx.lineH(7, 26, 29);
    mtrx.rect(33, 1, 38, 6, GFX_FILL);
    mtrx.lineV(32, 2, 5);
    mtrx.lineV(39, 2, 5);
    mtrx.lineH(0, 34, 37);
    mtrx.lineH(7, 34, 37);
    mtrx.rect(x1 + 24, y1, x1 + 25, y1 + 1, GFX_CLEAR);
    mtrx.rect(x1 + 32, y1, x1 + 33, y1 + 1, GFX_CLEAR);
    mtrx.update();
    delay(10);
    a++;
    if (a >= t) {
      t = random(500, 1000);
      x1 = random(1, 6);
      y1 = random(1, 6);
      if (x1 == 1 || x1 == 6) {
        y1 = 3;
      }
      if (y1 == 1 || y1 == 6) {
        x1 = 3;
      }
      a = 0;
    }
    flag = 0;
  }
  if (digitalRead(EN_MATRIX) == 1) {
    if (flag == 0) {
      mtrx.clear();
      mtrx.update();
      flag = 1;
    }
  }
}
