#include <VolAnalyzer.h>
#include <GyverMAX7219.h>
#include <FastLED.h>

MAX7219 < 5, 1, 10 > mtrx;   // одна матрица (1х1), пин CS на D5
VolAnalyzer analyzer(A0);  // микрофон на А0

int x1 = 3;
int y1 = 3;

void setup() {
  mtrx.begin();       // запускаем
  mtrx.setBright(10);  // яркость 0..15
  mtrx.clear();
  randomSeed(analogRead(A1));
  Serial.begin(9600);
}
void loop() {
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
  delay(1000);
  x1 = random(1, 6);
  y1 = random(1, 6);
  if (x1 == 1 || x1 == 6) {
    y1 = 3;
  }
  if (y1 == 1 || y1 == 6) {
    x1 = 3;
  }
}
