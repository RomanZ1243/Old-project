#include <TFT.h>                 // Подключаем библиотеку TFT  
#include <SPI.h>                 // Подключаем библиотеку SPI

#define cs   10                  // Указываем пины cs
#define dc   9                   // Указываем пины dc (A0)
#define rst  8                   // Указываем пины reset

TFT TFTscreen = TFT(cs, dc, rst);

int g;//градус
int x;
int y;
int x1;
int y1;

void setup()
{
  TFTscreen.begin();
  TFTscreen.background(255, 255, 255); // Очистим экран дисплея
  TFTscreen.setTextSize(2);      // Устанавливаем размер шрифта
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.circle(80, 64, 60);
  g = map(analogRead(A0), 0, 1023, 0, 360);
  x = cos(radians(g)) * 59 + 81;
  y = sin(radians(g)) * 59 + 65;
  x1 = x;
  y1 = y;
}

void loop()
{
  x1 = x;
  y1 = y;
  //g = map(analogRead(A0), 0, 1023, 0, 360);
  g++;
  if(g == 360)g = 0;
  delay(10);
  x = cos(radians(g)) * 59 + 80;
  y = sin(radians(g)) * 59 + 64;
  if (x1 != x || y1 != y) {
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.line(80, 64, x1, y1);
  }
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.line(80, 64, x, y);
}
