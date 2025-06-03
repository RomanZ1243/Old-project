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
int a;
int b;
int c;
int x;
int y;
int t1;//количество игроков
int t2;//кто ходит первым
int x1;//координаты в решетке
int y1;//координаты в решетке
int x2;//центр клетки
int y2;//центр клетки
int x3;//сохраняем координаты первого хода бота
int y3;//сохраняем координаты первого хода бота
int flag = 4;//режим
int flag1;//одно обновление и прорисовка графики
int flag2;//одно касание - один ход
int flag3;//одно обновление и прорисовка графики (в начале программы)
int score;
boolean num;//чей ход
int num1;//победитель
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
  randomSeed(analogRead(0));
  Serial.begin(9600);
}

void loop()
{
  if (flag2 == 1) {
    flag2 = 0;
  }
  if (flag1 == 2) {
    flag1 = 3;
  }
  if (flag == 4) {
    tft.fillScreen(ILI9341_WHITE);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setCursor(55, 5);
    tft.print("number of players");
    tft.setCursor(117, 75);//+10
    tft.print("1 motion");
    tft.setTextSize(3);
    tft.setCursor(137, 34);
    tft.print("1");
    tft.setCursor(167, 34);
    tft.print("2");
    tft.drawRect(130, 30, 59, 30, ILI9341_BLACK);
    tft.drawFastVLine(159, 31, 28, ILI9341_BLACK);
    tft.drawRect(130, 99, 59, 30, ILI9341_BLACK);
    tft.drawFastVLine(159, 100, 28, ILI9341_BLACK);
    tft.drawLine(134, 103, 155, 124, ILI9341_RED);
    tft.drawLine(155, 103, 134, 124, ILI9341_RED);
    tft.drawCircle(174, 114, 10, ILI9341_BLUE);
    tft.drawRect(132, 101, 26, 26, ILI9341_BLACK);
    tft.drawRect(110, 190, 100, 30, ILI9341_BLACK);
    tft.setTextSize(3);
    tft.setCursor(116, 195);
    tft.print("START");
    val[0][0] = 0;
    val[1][0] = 0;
    val[2][0] = 0;
    val[0][1] = 0;
    val[1][1] = 0;
    val[2][1] = 0;
    val[0][2] = 0;
    val[1][2] = 0;
    val[2][2] = 0;
    x = 0;
    y = 0;
    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = 0;
    t1 = 0;
    t2 = 0;
    num1 = 0;
    //flag3 = 1;
    flag2 = 0;
    flag1 = 0;
    flag = 0;
    score = 0;
    /*Serial.print(val[0][0]);
      Serial.print(val[0][1]);
      Serial.println(val[0][2]);
      Serial.print(val[1][0]);
      Serial.print(val[1][1]);
      Serial.println(val[1][2]);
      Serial.print(val[2][0]);
      Serial.print(val[2][1]);
      Serial.println(val[2][2]);
      Serial.println("          ");*/
  }
  while (ts.dataAvailable())        // Пока имеются данные с сенсорного модуля
  {
    ts.read();                      // Считываем с него данные
    x = ts.getX();                  // Считываем координату нажатия X
    y = ts.getY();                  // Считываем координату нажатия Y
    x = 320 - x;
    y = 240 - y;                 // Считываем координату нажатия Y
    if ((x != -1) && (y != -1))     // Если обе координаты в положительном диапазоне (т.е. если есть нажатие)
    {
      x += 4;                      // Корректируем координату с учетом калибровочных данных
      y -= 5;                       // Корректируем координату с учетом калибровочных данных
    }
    if (flag == 0) {/////////////////////////////////////////////
      if (x >= 130 && x <= 160 && y >= 30 && y <= 60) {
        tft.drawRect(132, 32, 26, 26, ILI9341_BLACK);
        tft.drawRect(161, 32, 26, 26, ILI9341_WHITE);
        t1 = 1;
      }
      if (x >= 160 && x <= 190 && y >= 30 && y <= 60) {
        tft.drawRect(132, 32, 26, 26, ILI9341_WHITE);
        tft.drawRect(161, 32, 26, 26, ILI9341_BLACK);
        t1 = 2;
      }
      if (x >= 130 && x <= 160 && y >= 99 && y <= 129) {
        tft.drawRect(132, 101, 26, 26, ILI9341_BLACK);
        tft.drawRect(161, 101, 26, 26, ILI9341_WHITE);
        t2 = 0;
      }
      if (x >= 160 && x <= 190 && y >= 99 && y <= 129) {
        tft.drawRect(132, 101, 26, 26, ILI9341_WHITE);
        tft.drawRect(161, 101, 26, 26, ILI9341_BLACK);
        t2 = 1;
      }
      if (t1 == 1) {
        tft.setTextColor(ILI9341_BLACK);
        tft.setTextSize(2);
        tft.setCursor(120, 140);
        tft.print("bot -");
        tft.drawLine(190, 140, 204, 154, ILI9341_RED);
        tft.drawLine(204, 140, 190, 154, ILI9341_RED);
      }
      if (t1 == 2) {
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(2);
        tft.setCursor(120, 140);
        tft.print("bot -");
        tft.drawLine(190, 140, 204, 154, ILI9341_WHITE);
        tft.drawLine(204, 140, 190, 154, ILI9341_WHITE);
      }
      if (flag1 == 0) {
        if (t1 > 0) {
          tft.fillRect(111, 191, 98, 28, ILI9341_BLUE);
          tft.setTextColor(ILI9341_WHITE);
          tft.setTextSize(3);
          tft.setCursor(116, 195);
          tft.print("START");
          flag1 = 1;
        }
      }
      if (x >= 110 && x <= 210 && y >= 190 && y <= 220 && flag1 == 1) {
        tft.fillRect(111, 191, 98, 28, ILI9341_CYAN);
        tft.setTextColor(ILI9341_BLACK);
        tft.setTextSize(3);
        tft.setCursor(116, 195);
        tft.print("START");
        flag2 = 1;
        flag1 = 0;
        flag = t1;
        num = t2;
      }
    }
    if (flag == 1) {/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if (flag1 == 0) {
        tft.fillScreen(ILI9341_WHITE);
        tft.drawLine(129, 29, 129, 209, ILI9341_BLACK);
        tft.drawLine(189, 29, 189, 209, ILI9341_BLACK);
        tft.drawLine(69, 89, 249, 89, ILI9341_BLACK);
        tft.drawLine(69, 149, 249, 149, ILI9341_BLACK);
        flag2 = 0;
        flag1 = 1;
      }
      if (t2 == 0) {
        if (flag2 == 0) {
          if (flag1 == 1) {
            if (num == 0) {
              if (score == 0) {
                x1 = random(0, 2) * 2;
                y1 = random(0, 2) * 2;
                x2 = 99 + 60 * x1;
                y2 = 59 + 60 * y1;
                krestik();
                val[y1][x1] = num + 1;
                num = ! num;
                flag2 = 1;
                flag1 = 2;
                score++;
              }
            }
          }
          if (flag1 == 3) {
            if (num == 1) {
              if (x >= 69 && x <= 250 && y >= 29 && y <= 210) {
                x1 = ceil((x - 69) / 60);
                y1 = ceil((y - 29) / 60);
              }
              if (val[y1][x1] == 0) {
                x2 = 99 + 60 * x1;
                y2 = 59 + 60 * y1;
                nolik();
                val[y1][x1] = 2;
                num = ! num;
                //flag2 = 1;
              }
              if (num == 0) {
                if (score == 1) {
                  if (abs(x3 - x1) == 1 && y3 == y1) {
                    x1 = x3;
                    y1 = abs(y3 - 2);
                    x2 = 99 + 60 * x1;
                    y2 = 59 + 60 * y1;
                    krestik();
                    val[y1][x1] = 1;
                    num = ! num;
                    flag2 = 1;
                  }
                  if (abs(y3 - y1) == 1 && x3 == x1) {
                    x1 = abs(x3 - 2);
                    y1 = y3;
                    x2 = 99 + 60 * x1;
                    y2 = 59 + 60 * y1;
                    krestik();
                    val[y1][x1] = 1;
                    num = ! num;
                    flag2 = 1;
                    score++;
                  }
                }
              }
              if (num == 0) {
                if (score == 2) {
                  if (check2() == 0) {
                    x1 = random(0, 2);
                    if (x1 == 0) {
                      x1 = abs(x3 - 2);
                      y1 = abs(x3 - 2);
                    }
                    if (x1 == 1) {
                      y1 = 1;
                    }
                    x2 = 99 + 60 * x1;
                    y2 = 59 + 60 * y1;
                    krestik();
                    val[y1][x1] = 1;
                    num = ! num;
                    flag2 = 1;
                    score++;
                  }
                  else {
                    a = check2() / 100;
                    b = (check2() - a * 100) / 10;
                    c = check2() % 10;
                    x1 = b;
                    y1 = c;
                    x2 = 99 + 60 * x1;
                    y2 = 59 + 60 * y1;
                    krestik();
                    val[y1][x1] = 1;
                    num = ! num;
                    flag2 = 1;
                    score++;
                  }
                }
                if (score == 3) {
                  a = check2() / 100;
                  b = (check2() - a * 100) / 10;
                  c = check2() % 10;
                  x1 = b;
                  y1 = c;
                  x2 = 99 + 60 * x1;
                  y2 = 59 + 60 * y1;
                  krestik();
                  val[y1][x1] = 1;
                  num = ! num;
                  flag2 = 1;
                  score++;
                }
              }
            }
          }
          Serial.println(score);
        }
      }
      check();
      //check2();
    }
    if (flag == 2) {/////////////////////////////////////////////////////////////////////////////////////////////////
      if (flag1 == 0) {
        tft.fillScreen(ILI9341_WHITE);
        tft.drawLine(129, 29, 129, 209, ILI9341_BLACK);
        tft.drawLine(189, 29, 189, 209, ILI9341_BLACK);
        tft.drawLine(69, 89, 249, 89, ILI9341_BLACK);
        tft.drawLine(69, 149, 249, 149, ILI9341_BLACK);
        flag1 = 1;
      }
      if (flag2 == 0) {
        /*Serial.print(val[0][0]);
          Serial.print(val[0][1]);
          Serial.println(val[0][2]);
          Serial.print(val[1][0]);
          Serial.print(val[1][1]);
          Serial.println(val[1][2]);
          Serial.print(val[2][0]);
          Serial.print(val[2][1]);
          Serial.println(val[2][2]);
          Serial.println("          ");*/
        if (x >= 69 && x <= 250 && y >= 29 && y <= 210) {
          x1 = ceil((x - 69) / 60);
          y1 = ceil((y - 29) / 60);
        }
        if (val[y1][x1] == 0) {
          x2 = 99 + 60 * x1;
          y2 = 59 + 60 * y1;
          if (num == 0) {
            krestik();
            val[y1][x1] = 1;
          }
          if (num == 1) {
            nolik();
            val[y1][x1] = 2;
          }
          check();
          num = ! num;
          flag2 = 1;
        }
      }

    }
    if (flag == 3) {/////////////////////////////////////////////////////////////////////////////////
      if (flag1 == 0) {
        if (num1 == 3) {
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(3);
          tft.setCursor(7, 89);
          tft.print("TIE");
        }
        else {
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(3);
          tft.setCursor(7, 89);
          tft.print("won");
          if (num1 == 1) {
            tft.drawLine(17, 116, 47, 146, ILI9341_RED);
            tft.drawLine(47, 116, 17, 146, ILI9341_RED);
          }
          else {
            tft.drawCircle(32, 131, 15, ILI9341_BLUE);
          }
        }

        tft.drawRect(119, 213, 80, 26, ILI9341_BLACK);
        tft.fillRect(120, 214, 78, 24, ILI9341_BLUE);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(2);
        tft.setCursor(137, 218);
        tft.print("MENU");
        flag1 = 1;
      }
      //Serial.println(1);
      if (x >= 120 && x <= 198 && y >= 214 && y <= 238) {
        Serial.println(1);
        tft.fillRect(120, 214, 78, 24, ILI9341_CYAN);
        tft.setTextColor(ILI9341_BLACK);
        tft.setTextSize(2);
        tft.setCursor(137, 218);
        tft.print("MENU");
        flag1 = 0;
        flag = 4;
      }
    }
  }
  /*Serial.print("x = ");
    Serial.print(x1);
    Serial.print("; y = ");
    Serial.println(y1);*/
}

void krestik() {
  tft.drawLine(x2 - 25, y2 - 25, x2 + 25, y2 + 25, ILI9341_RED);
  tft.drawLine(x2 - 24, y2 - 26, x2 + 26, y2 + 24, ILI9341_RED);
  tft.drawLine(x2 - 26, y2 - 24, x2 + 24, y2 + 26, ILI9341_RED);
  tft.drawLine(x2 - 24, y2 - 25, x2 + 25, y2 + 24, ILI9341_RED);
  tft.drawLine(x2 - 25, y2 - 24, x2 + 24, y2 + 25, ILI9341_RED);
  tft.drawLine(x2 + 25, y2 - 25, x2 - 25, y2 + 25, ILI9341_RED);
  tft.drawLine(x2 + 24, y2 - 26, x2 - 26, y2 + 24, ILI9341_RED);
  tft.drawLine(x2 + 26, y2 - 24, x2 - 24, y2 + 26, ILI9341_RED);
  tft.drawLine(x2 + 24, y2 - 25, x2 - 25, y2 + 24, ILI9341_RED);
  tft.drawLine(x2 + 25, y2 - 24, x2 - 24, y2 + 25, ILI9341_RED);
}

void nolik() {
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
}

void check() {
  if (val[0][0] > 0 && val[0][1] > 0 && val[0][2] > 0 && val[0][0] == val[0][1] && val[0][0] == val[0][2]) {
    tft.drawLine(69, 59, 249, 59, ILI9341_BLACK);
    tft.drawLine(69, 58, 249, 58, ILI9341_BLACK);
    tft.drawLine(69, 60, 249, 60, ILI9341_BLACK);
    num1 = val[0][0];
    flag1 = 0;
    flag = 3;
  }
  if (val[1][0] > 0 && val[1][1] > 0 && val[1][2] > 0 && val[1][0] == val[1][1] && val[1][0] == val[1][2]) {
    tft.drawLine(69, 119, 249, 119, ILI9341_BLACK);
    tft.drawLine(69, 118, 249, 118, ILI9341_BLACK);
    tft.drawLine(69, 120, 249, 120, ILI9341_BLACK);
    num1 = val[1][0];
    flag1 = 0;
    flag = 3;
  }
  if (val[2][0] > 0 && val[2][1] > 0 && val[2][2] > 0 && val[2][0] == val[2][1] && val[2][0] == val[2][2]) {
    tft.drawLine(69, 179, 249, 179, ILI9341_BLACK);
    tft.drawLine(69, 178, 249, 178, ILI9341_BLACK);
    tft.drawLine(69, 180, 249, 180, ILI9341_BLACK);
    num1 = val[2][0];
    flag1 = 0;
    flag = 3;
  }
  if (val[0][0] > 0 && val[1][0] > 0 && val[2][0] > 0 && val[0][0] == val[1][0] && val[0][0] == val[2][0]) {
    tft.drawLine(99, 29, 99, 209, ILI9341_BLACK);
    tft.drawLine(98, 29, 98, 209, ILI9341_BLACK);
    tft.drawLine(100, 29, 100, 209, ILI9341_BLACK);
    num1 = val[0][0];
    flag1 = 0;
    flag = 3;
  }
  if (val[0][1] > 0 && val[1][1] > 0 && val[2][1] > 0 && val[0][1] == val[1][1] && val[0][1] == val[2][1]) {
    tft.drawLine(159, 29, 159, 209, ILI9341_BLACK);
    tft.drawLine(158, 29, 158, 209, ILI9341_BLACK);
    tft.drawLine(160, 29, 160, 209, ILI9341_BLACK);
    num1 = val[0][1];
    flag1 = 0;
    flag = 3;
  }
  if (val[0][2] > 0 && val[1][2] > 0 && val[2][2] > 0 && val[0][2] == val[1][2] && val[0][2] == val[2][2]) {
    tft.drawLine(219, 29, 219, 209, ILI9341_BLACK);
    tft.drawLine(218, 29, 218, 209, ILI9341_BLACK);
    tft.drawLine(220, 29, 220, 209, ILI9341_BLACK);
    num1 = val[0][2];
    flag1 = 0;
    flag = 3;
  }
  if (val[0][0] > 0 && val[1][1] > 0 && val[2][2] > 0 && val[0][0] == val[1][1] && val[0][0] == val[2][2]) {
    tft.drawLine(69, 29, 249, 209, ILI9341_BLACK);
    tft.drawLine(70, 28, 250, 208, ILI9341_BLACK);
    tft.drawLine(68, 30, 248, 210, ILI9341_BLACK);
    tft.drawLine(70, 29, 249, 208, ILI9341_BLACK);
    tft.drawLine(69, 30, 248, 209, ILI9341_BLACK);
    num1 = val[0][0];
    flag1 = 0;
    flag = 3;
  }
  if (val[2][0] > 0 && val[1][1] > 0 && val[0][2] > 0 && val[2][0] == val[1][1] && val[2][0] == val[0][2]) {
    tft.drawLine(249, 29, 69, 209, ILI9341_BLACK);
    tft.drawLine(248, 28, 68, 208, ILI9341_BLACK);
    tft.drawLine(250, 30, 70, 210, ILI9341_BLACK);
    tft.drawLine(248, 29, 69, 208, ILI9341_BLACK);
    tft.drawLine(249, 30, 70, 209, ILI9341_BLACK);
    num1 = val[2][0];
    flag1 = 0;
    flag = 3;
  }
  else {
    if (val[0][0] > 0 && val[0][1] > 0 && val[0][2] > 0 && val[1][0] > 0 && val[1][1] > 0 && val[1][2] > 0 && val[2][0] > 0 && val[2][1] > 0 && val[2][2] > 0 && num1 == 0) {
      num1 = 3;
      flag1 = 0;
      flag = 3;
    }
  }
}

int check2() {
  if (val[0][0] == val[0][1] && val[0][0] > 0 && val[0][2] == 0) {
    return (val[0][0] * 100 + 2);
  }
  if (val[0][1] == val[0][2] && val[0][1] > 0 && val[0][0] == 0) {
    return (val[0][1] * 100);
  }
  if (val[0][0] == val[0][2] && val[0][0] > 0 && val[0][1] == 0) {
    return (val[0][0] * 100 + 1);
  }

  if (val[1][0] == val[1][1] && val[1][0] > 0 && val[1][2] == 0) {
    return (val[1][0] * 100 + 10 + 2);
  }
  if (val[1][1] == val[1][2] && val[1][1] > 0 && val[1][0] == 0) {
    return (val[1][1] * 100 + 10);
  }
  if (val[1][0] == val[1][2] && val[1][0] > 0 && val[1][1] == 0) {
    return (val[1][0] * 100 + 10 + 1);
  }

  if (val[2][0] == val[2][1] && val[2][0] > 0 && val[2][2] == 0) {
    return (val[2][0] * 100 + 20 + 2);
  }
  if (val[2][1] == val[2][2] && val[2][1] > 0 && val[2][0] == 0) {
    return (val[2][1] * 100 + 20);
  }
  if (val[2][0] == val[2][2] && val[2][0] > 0 && val[2][1] == 0) {
    return (val[2][0] * 100 + 20 + 1);
  }

  if (val[0][0] == val[1][0] && val[0][0] > 0 && val[2][0] == 0) {////////////////////////////////////
    return (val[0][0] * 100 + 20);
  }
  if (val[1][0] == val[2][0] && val[1][0] > 0 && val[0][0] == 0) {
    return (val[1][0] * 100);
  }
  if (val[0][0] == val[2][0] && val[0][0] > 0 && val[1][0] == 0) {
    return (val[0][0] * 100 + 10);
  }

  if (val[0][1] == val[1][1] && val[0][1] > 0 && val[2][1] == 0) {
    return (val[0][1] * 100 + 20 + 1);
  }
  if (val[1][1] == val[2][1] && val[1][1] > 0 && val[0][1] == 0) {
    return (val[1][1] * 100 + 1);
  }
  if (val[0][1] == val[2][1] && val[0][1] > 0 && val[1][1] == 0) {
    return (val[0][1] * 100 + 10 + 1);
  }

  if (val[0][2] == val[1][2] && val[0][2] > 0 && val[2][2] == 0) {
    return (val[0][2] * 100 + 20 + 2);
  }
  if (val[1][2] == val[2][2] && val[1][2] > 0 && val[0][2] == 0) {
    return (val[1][2] * 100 + 2);
  }
  if (val[0][2] == val[2][2] && val[0][2] > 0 && val[1][2] == 0) {
    return (val[0][2] * 100 + 10 + 2);
  }
}
