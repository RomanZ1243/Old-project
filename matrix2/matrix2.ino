#include <VolAnalyzer.h>
#include <GyverMAX7219.h>
#include <FastLED.h>

MAX7219 < 4, 1, 5 > mtrx;   // одна матрица (1х1), пин CS на D5
VolAnalyzer analyzer(A0);  // микрофон на А0

int y;
int x;
int i;
int flag;

void setup() {
  mtrx.begin();       // запускаем
  mtrx.setBright(10);  // яркость 0..15
  mtrx.clear();
  Serial.begin(9600);
  // переключаем на внешнее опорное
  // его подключаем к 3.3V
  //analogReference(EXTERNAL);
}
void loop() {
  uint8_t x = 0 + i * 8;
    mtrx.rect(1 + x, 1, 6 + x, 6, GFX_FILL);
    mtrx.lineV(0 + x, 2, 5);
    mtrx.lineV(7 + x, 2, 5);
    mtrx.lineH(0, 2 + x, 5 + x);
    mtrx.lineH(7, 2 + x, 5 + x);
    x += 24 + i * 8;
    mtrx.rect(0, 3, 5, 2, GFX_CLEAR);
    mtrx.update();
}
