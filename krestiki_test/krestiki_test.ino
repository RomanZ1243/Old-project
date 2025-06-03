#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "URTouch.h"

#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_CLK 13

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#define t_SCK 3
#define t_CS 4
#define t_MOSI 5
#define t_MISO 6
#define t_IRQ 7

URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ);

int t1;//количество игроков
int t2;//кто ходит первым
int x1;//координаты в решетке
int y1;//координаты в решетке
int x2 = 180;//центр клетки
int y2 = 120;//центр клетки
int flag;//режим
int flag1;//одно обновление и прорисовка графики
int flag2;//одно касание - один ход
boolean num;//чей ход
int val[3][3] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
};//все ходы


void setup() {
  tft.begin();
  tft.setRotation(1);

  ts.InitTouch();
  ts.setPrecision(PREC_EXTREME);
  tft.fillScreen(ILI9341_WHITE);
  
  tft.drawCircle(x2, y2, 26, ILI9341_BLUE);
  tft.drawCircle(x2, y2, 25, ILI9341_BLUE);
  tft.drawCircle(x2, y2, 24, ILI9341_BLUE);
  tft.drawCircle(x2, y2, 23, ILI9341_BLUE);
  tft.drawPixel(x2 + 5, y2 - 25, ILI9341_BLUE);
  tft.drawPixel(x2 + 11, y2 - 23, ILI9341_BLUE);
  tft.drawPixel(x2 + 13, y2 - 22, ILI9341_BLUE);
  tft.drawPixel(x2 + 14, y2 - 20, ILI9341_BLUE);
  tft.drawPixel(x2 + 15, y2 - 18, ILI9341_BLUE);
  tft.drawPixel(x2 + 18, y2 - 18, ILI9341_BLUE);
  tft.drawPixel(x2 + 17, y2 - 19, ILI9341_BLUE);
  tft.drawPixel(x2 + 19, y2 - 17, ILI9341_BLUE);
  tft.drawPixel(x2 + 20, y2 - 14, ILI9341_BLUE);
  tft.drawPixel(x2 + 18, y2 - 15, ILI9341_BLUE);
  tft.drawPixel(x2 + 22, y2 - 13, ILI9341_BLUE);
  tft.drawPixel(x2 + 23, y2 - 11, ILI9341_BLUE);
  tft.drawPixel(x2 + 25, y2 - 5, ILI9341_BLUE);

  tft.drawPixel(x2 - 5, y2 - 25, ILI9341_BLUE);
  tft.drawPixel(x2 - 11, y2 - 23, ILI9341_BLUE);
  tft.drawPixel(x2 - 13, y2 - 22, ILI9341_BLUE);
  tft.drawPixel(x2 - 14, y2 - 20, ILI9341_BLUE);
  tft.drawPixel(x2 - 15, y2 - 18, ILI9341_BLUE);
  tft.drawPixel(x2 - 18, y2 - 18, ILI9341_BLUE);
  tft.drawPixel(x2 - 17, y2 - 19, ILI9341_BLUE);
  tft.drawPixel(x2 - 19, y2 - 17, ILI9341_BLUE);
  tft.drawPixel(x2 - 20, y2 - 14, ILI9341_BLUE);
  tft.drawPixel(x2 - 18, y2 - 15, ILI9341_BLUE);
  tft.drawPixel(x2 - 22, y2 - 13, ILI9341_BLUE);
  tft.drawPixel(x2 - 23, y2 - 11, ILI9341_BLUE);
  tft.drawPixel(x2 - 25, y2 - 5, ILI9341_BLUE);

  tft.drawPixel(x2 - 5, y2 + 25, ILI9341_BLUE);
  tft.drawPixel(x2 - 11, y2 + 23, ILI9341_BLUE);
  tft.drawPixel(x2 - 13, y2 + 22, ILI9341_BLUE);
  tft.drawPixel(x2 - 14, y2 + 20, ILI9341_BLUE);
  tft.drawPixel(x2 - 15, y2 + 18, ILI9341_BLUE);
  tft.drawPixel(x2 - 18, y2 + 18, ILI9341_BLUE);
  tft.drawPixel(x2 - 17, y2 + 19, ILI9341_BLUE);
  tft.drawPixel(x2 - 19, y2 + 17, ILI9341_BLUE);
  tft.drawPixel(x2 - 20, y2 + 14, ILI9341_BLUE);
  tft.drawPixel(x2 - 18, y2 + 15, ILI9341_BLUE);
  tft.drawPixel(x2 - 22, y2 + 13, ILI9341_BLUE);
  tft.drawPixel(x2 - 23, y2 + 11, ILI9341_BLUE);
  tft.drawPixel(x2 - 25, y2 + 5, ILI9341_BLUE);

  tft.drawPixel(x2 + 5, y2 + 25, ILI9341_BLUE);
  tft.drawPixel(x2 + 11, y2 + 23, ILI9341_BLUE);
  tft.drawPixel(x2 + 13, y2 + 22, ILI9341_BLUE);
  tft.drawPixel(x2 + 14, y2 + 20, ILI9341_BLUE);
  tft.drawPixel(x2 + 15, y2 + 18, ILI9341_BLUE);
  tft.drawPixel(x2 + 18, y2 + 18, ILI9341_BLUE);
  tft.drawPixel(x2 + 17, y2 + 19, ILI9341_BLUE);
  tft.drawPixel(x2 + 19, y2 + 17, ILI9341_BLUE);
  tft.drawPixel(x2 + 20, y2 + 14, ILI9341_BLUE);
  tft.drawPixel(x2 + 18, y2 + 15, ILI9341_BLUE);
  tft.drawPixel(x2 + 22, y2 + 13, ILI9341_BLUE);
  tft.drawPixel(x2 + 23, y2 + 11, ILI9341_BLUE);
  tft.drawPixel(x2 + 25, y2 + 5, ILI9341_BLUE);
  
  Serial.begin(9600);
}

void loop() {

}
