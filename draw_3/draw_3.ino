#include "Adafruit_GFX.h"     // Библиотека обработчика графики
#include "Adafruit_ILI9341.h" // Программные драйвера для дисплеев ILI9341
#include "URTouch.h"          // Библиотека для работы с сенсорным экраном

#define TFT_DC 9              // Пин подключения вывода D/C дисплея
#define TFT_CS 10             // Пин подключения вывода CS дисплея
#define TFT_RST 8             // Пин подключения вывода RESET (Если подключен к питанию или кнопке, то эту строку закомментировать, а следующую раскомментировать)
#define TFT_MISO 12           // Пин подключения вывода дисплея SDO(MISO)
#define TFT_MOSI 11           // Пин подключения вывода дисплея SDI(MOSI)
#define TFT_CLK 13            // Пин подключения вывода дисплея SCK

int flag;
int flag1;
int flag2;
int radius = 4;
int radius1;
int a;
int b;
int a1;
int b1;
int a2;
int b2;
int a3;
int b3;
int aa;
int bb;
int z;
int x1;
int y1;
int y2;
int y3;
boolean y4;
int y5;
int y6;
int y7;
int y8;
int y9;
int r;
int r1;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);  // Создаем объект дисплея и сообщаем библиотеке распиновку для работы с графикой

#define t_SCK 3               // Пин подключения вывода дисплея T_CLK
#define t_CS 4                // Пин подключения вывода дисплея T_CS
#define t_MOSI 5              // Пин подключения вывода дисплея T_DIN
#define t_MISO 6              // Пин подключения вывода дисплея T_DOUT
#define t_IRQ 7               // Пин подключения вывода дисплея T_IRQ

URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ); // Создаем объект сенсорного модуля и сообщаем библиотеке распиновку для работы с ним

void setup() {
  tft.begin();                      // Инициализируем начало работы с графическим дисплеем
  tft.setRotation(1);               // Переводим дисплей в альбомную ориентацию
  ts.InitTouch();                   // Инициализируем сенсорный модуль дисплея
  ts.setPrecision(PREC_EXTREME);
  Serial.begin(9600);// Определяем необходимую точность обработки нажатий: PREC_LOW - низкая, PREC_MEDIUM - средняя, PREC_HI - высокая, PREC_EXTREME - максимальная
  tft.fillScreen(ILI9341_WHITE);
  //tft.drawRect(293, 0, 27, 227, ILI9341_BLACK);
  tft.drawLine(294, 0, 294, 233, ILI9341_BLACK);
  tft.drawLine(294, 233, 320, 233, ILI9341_BLACK);
  tft.drawLine(295, 25, 320, 25, ILI9341_BLACK);
  tft.drawLine(295, 51, 320, 51, ILI9341_BLACK);
  tft.drawLine(295, 77, 320, 77, ILI9341_BLACK);
  tft.drawLine(295, 103, 320, 103, ILI9341_BLACK);
  tft.drawLine(295, 129, 320, 129, ILI9341_BLACK);
  tft.drawLine(295, 155, 320, 155, ILI9341_BLACK);
  tft.drawLine(295, 181, 320, 181, ILI9341_BLACK);
  tft.drawLine(295, 207, 320, 207, ILI9341_BLACK);
  tft.fillRect(295, 0, 25, 25, ILI9341_BLACK);
  tft.fillRect(295, 26, 25, 25, ILI9341_BLUE);
  tft.fillRect(295, 52, 25, 25, ILI9341_RED);
  tft.fillRect(295, 78, 25, 25, ILI9341_GREEN);
  tft.fillRect(295, 104, 25, 25, ILI9341_CYAN);
  tft.fillRect(295, 130, 25, 25, ILI9341_MAGENTA);
  tft.fillRect(295, 156, 25, 25, ILI9341_YELLOW);
  tft.fillRect(295, 182, 25, 25, ILI9341_WHITE);
  tft.drawRect(303, 213, 10, 15, ILI9341_BLACK);
  tft.fillRect(303, 220, 10, 7, ILI9341_BLACK);
  tft.drawRect(296, 1, 23, 23, ILI9341_WHITE);
  tft.drawLine(97, 0, 97, 35, ILI9341_BLACK);//radius
  tft.drawLine(200, 0, 200, 35, ILI9341_BLACK);//radius
  tft.drawLine(62, 0, 62, 35, ILI9341_BLACK);//слева
  tft.drawLine(27, 0, 27, 35, ILI9341_BLACK);//слева
  tft.drawLine(235, 0, 235, 35, ILI9341_BLACK);//справа
  tft.drawLine(270, 0, 270, 35, ILI9341_BLACK);//справа
  tft.drawLine(27, 35, 270, 35, ILI9341_BLACK);//основа сверху
  tft.drawLine(225, 10, 210, 25, ILI9341_BLACK);//линия сверху
  tft.drawRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
  tft.drawCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
  tft.drawRoundRect (102, 5, 25, 25, 3, ILI9341_BLACK);//-
  tft.drawRoundRect (170, 5, 25, 25, 3, ILI9341_BLACK);//+
  if (radius < 10) {
    x1 = 141;
  }
  if (radius == 10) {
    x1 = 132;
  }
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(3);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(x1, 7);             // Определяем координаты верхнего левого угла области вывода
  tft.print(radius);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(3);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(107, 7);             // Определяем координаты верхнего левого угла области вывода
  tft.print("-");
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(3);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(175, 7);             // Определяем координаты верхнего левого угла области вывода
  tft.print("+");
}

void loop() {
  int x, y;                         // Переменные для работы с координатами нажатий
  if (flag2 == 0) {
    tft.fillRoundRect (103, 6, 23, 23, 2, ILI9341_WHITE);
    tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
    tft.setTextSize(3);               // Определяем размер шрифта для вывода на дисплей
    tft.setCursor(107, 7);             // Определяем координаты верхнего левого угла области вывода
    tft.print("-");
    flag2 = 1;
  }
  if (flag1 == 0) {
    tft.fillRoundRect (171, 6, 23, 23, 2, ILI9341_WHITE);
    tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
    tft.setTextSize(3);               // Определяем размер шрифта для вывода на дисплей
    tft.setCursor(175, 7);             // Определяем координаты верхнего левого угла области вывода
    tft.print("+");
    flag1 = 1;
  }
  y2 = 1;
  y5 = 1;
  y6 = 0;
  y7 = 0;
  y9 = 0;
  r = 0;
  while (ts.dataAvailable())        // Пока имеются данные с сенсорного модуля
  {
    ts.read();                      // Считываем с него данные
    x = ts.getX();                  // Считываем координату нажатия X
    y = ts.getY();                  // Считываем координату нажатия Y
    x = 320 - x;
    y = 240 - y;
    if ((x != -1) && (y != -1))     // Если обе координаты в положительном диапазоне (т.е. если есть нажатие)
    {
      x += 4;                      // Корректируем координату с учетом калибровочных данных
      y -= 5;
      if (294 < x && x < 320) {
        if (0 < y && y < 25) {
          tft.drawRect(296, 1, 23, 23, ILI9341_WHITE);
          tft.drawRect(296, 27, 23, 23, ILI9341_BLUE);
          tft.drawRect(296, 53, 23, 23, ILI9341_RED);
          tft.drawRect(296, 79, 23, 23, ILI9341_GREEN);
          tft.drawRect(296, 105, 23, 23, ILI9341_CYAN);
          tft.drawRect(296, 131, 23, 23, ILI9341_MAGENTA);
          tft.drawRect(296, 157, 23, 23, ILI9341_YELLOW);
          tft.drawRect(296, 183, 23, 23, ILI9341_WHITE);
          tft.drawRect(296, 209, 23, 23, ILI9341_WHITE);
          z = 0;
        }
        if (26 < y && y < 51) {
          tft.drawRect(296, 1, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 27, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 53, 23, 23, ILI9341_RED);
          tft.drawRect(296, 79, 23, 23, ILI9341_GREEN);
          tft.drawRect(296, 105, 23, 23, ILI9341_CYAN);
          tft.drawRect(296, 131, 23, 23, ILI9341_MAGENTA);
          tft.drawRect(296, 157, 23, 23, ILI9341_YELLOW);
          tft.drawRect(296, 183, 23, 23, ILI9341_WHITE);
          tft.drawRect(296, 209, 23, 23, ILI9341_WHITE);
          z = 1;
        }
        if (52 < y && y < 77) {
          tft.drawRect(296, 1, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 27, 23, 23, ILI9341_BLUE);
          tft.drawRect(296, 53, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 79, 23, 23, ILI9341_GREEN);
          tft.drawRect(296, 105, 23, 23, ILI9341_CYAN);
          tft.drawRect(296, 131, 23, 23, ILI9341_MAGENTA);
          tft.drawRect(296, 157, 23, 23, ILI9341_YELLOW);
          tft.drawRect(296, 183, 23, 23, ILI9341_WHITE);
          tft.drawRect(296, 209, 23, 23, ILI9341_WHITE);
          z = 2;
        }
        if (78 < y && y < 103) {
          tft.drawRect(296, 1, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 27, 23, 23, ILI9341_BLUE);
          tft.drawRect(296, 53, 23, 23, ILI9341_RED);
          tft.drawRect(296, 79, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 105, 23, 23, ILI9341_CYAN);
          tft.drawRect(296, 131, 23, 23, ILI9341_MAGENTA);
          tft.drawRect(296, 157, 23, 23, ILI9341_YELLOW);
          tft.drawRect(296, 183, 23, 23, ILI9341_WHITE);
          tft.drawRect(296, 209, 23, 23, ILI9341_WHITE);
          z = 3;
        }
        if (104 < y && y < 129) {
          tft.drawRect(296, 1, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 27, 23, 23, ILI9341_BLUE);
          tft.drawRect(296, 53, 23, 23, ILI9341_RED);
          tft.drawRect(296, 79, 23, 23, ILI9341_GREEN);
          tft.drawRect(296, 105, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 131, 23, 23, ILI9341_MAGENTA);
          tft.drawRect(296, 157, 23, 23, ILI9341_YELLOW);
          tft.drawRect(296, 183, 23, 23, ILI9341_WHITE);
          tft.drawRect(296, 209, 23, 23, ILI9341_WHITE);
          z = 4;
        }
        if (130 < y && y < 155) {
          tft.drawRect(296, 1, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 27, 23, 23, ILI9341_BLUE);
          tft.drawRect(296, 53, 23, 23, ILI9341_RED);
          tft.drawRect(296, 79, 23, 23, ILI9341_GREEN);
          tft.drawRect(296, 105, 23, 23, ILI9341_CYAN);
          tft.drawRect(296, 131, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 157, 23, 23, ILI9341_YELLOW);
          tft.drawRect(296, 183, 23, 23, ILI9341_WHITE);
          tft.drawRect(296, 209, 23, 23, ILI9341_WHITE);
          z = 5;
        }
        if (156 < y && y < 181) {
          tft.drawRect(296, 1, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 27, 23, 23, ILI9341_BLUE);
          tft.drawRect(296, 53, 23, 23, ILI9341_RED);
          tft.drawRect(296, 79, 23, 23, ILI9341_GREEN);
          tft.drawRect(296, 105, 23, 23, ILI9341_CYAN);
          tft.drawRect(296, 131, 23, 23, ILI9341_MAGENTA);
          tft.drawRect(296, 157, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 183, 23, 23, ILI9341_WHITE);
          tft.drawRect(296, 209, 23, 23, ILI9341_WHITE);
          z = 6;
        }
        if (182 < y && y < 212) {
          tft.drawRect(296, 1, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 27, 23, 23, ILI9341_BLUE);
          tft.drawRect(296, 53, 23, 23, ILI9341_RED);
          tft.drawRect(296, 79, 23, 23, ILI9341_GREEN);
          tft.drawRect(296, 105, 23, 23, ILI9341_CYAN);
          tft.drawRect(296, 131, 23, 23, ILI9341_MAGENTA);
          tft.drawRect(296, 157, 23, 23, ILI9341_YELLOW);
          tft.drawRect(296, 183, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 209, 23, 23, ILI9341_WHITE);
          z = 7;
        }
        if (213 < y && y < 233) {
          tft.drawRect(296, 1, 23, 23, ILI9341_BLACK);
          tft.drawRect(296, 27, 23, 23, ILI9341_BLUE);
          tft.drawRect(296, 53, 23, 23, ILI9341_RED);
          tft.drawRect(296, 79, 23, 23, ILI9341_GREEN);
          tft.drawRect(296, 105, 23, 23, ILI9341_CYAN);
          tft.drawRect(296, 131, 23, 23, ILI9341_MAGENTA);
          tft.drawRect(296, 157, 23, 23, ILI9341_YELLOW);
          tft.drawRect(296, 183, 23, 23, ILI9341_WHITE);
          tft.drawRect(296, 209, 23, 23, ILI9341_BLACK);
          tft.fillRect(0, 36, 294, 204, ILI9341_WHITE);
        }
      }
      if (y3 == 0) {
        if (x < 294 - radius && y > 35 + radius) {
          if (z == 0) {
            tft.fillCircle(x, y, radius, ILI9341_BLACK);
          }
          if (z == 1) {
            tft.fillCircle(x, y, radius, ILI9341_BLUE);
          }
          if (z == 2) {
            tft.fillCircle(x, y, radius, ILI9341_RED);
          }
          if (z == 3) {
            tft.fillCircle(x, y, radius, ILI9341_GREEN);
          }
          if (z == 4) {
            tft.fillCircle(x, y, radius, ILI9341_CYAN);
          }
          if (z == 5) {
            tft.fillCircle(x, y, radius, ILI9341_MAGENTA);
          }
          if (z == 6) {
            tft.fillCircle(x, y, radius, ILI9341_YELLOW);
          }
          if (z == 7) {
            tft.fillCircle(x, y, radius, ILI9341_WHITE);
          }
        }
      }
      if (y3 == 1) {
        if (x < 294 && y > 35) {
          if (y6 == 0) {
            a = x;
            b = y;
            a2 = a;
            b2 = b;
            y6 = 1;
          }
          if (y6 == 1) {
            aa = a2;
            bb = b2;
            a2 = x;
            b2 = y;
            if (aa != a2 || bb != b2) {
              if (y4 == 0) {
                if (aa < a && bb < b) {
                  tft.drawRect(aa, bb, a - aa, b - bb, ILI9341_WHITE);
                }
                if (aa > a && bb > b) {
                  tft.drawRect(a, b, aa - a, bb - b, ILI9341_WHITE);
                }
                if (aa > a && bb < b) {
                  tft.drawRect(a, b - (b - bb), aa - a, b - bb, ILI9341_WHITE);
                }
                if (aa < a && bb > b) {
                  tft.drawRect(a - (a - aa), b, a - aa, bb - b, ILI9341_WHITE);
                }
              }
              if (y4 == 1) {
                if (aa < a && bb < b) {
                  tft.fillRect(aa, bb, a - aa, b - bb, ILI9341_WHITE);
                }
                if (aa > a && bb > b) {
                  tft.fillRect(a, b, aa - a, bb - b, ILI9341_WHITE);
                }
                if (aa > a && bb < b) {
                  tft.fillRect(a, b - (b - bb), aa - a, b - bb, ILI9341_WHITE);
                }
                if (aa < a && bb > b) {
                  tft.fillRect(a - (a - aa), b, a - aa, bb - b, ILI9341_WHITE);
                }
              }
            }
            if (a2 < a && b2 < b) {
              if (y4 == 0) {
                if (z == 0) {
                  tft.drawRect(a2, b2, a - a2, b - b2, ILI9341_BLACK);
                }
                if (z == 1) {
                  tft.drawRect(a2, b2, a - a2, b - b2, ILI9341_BLUE);
                }
                if (z == 2) {
                  tft.drawRect(a2, b2, a - a2, b - b2, ILI9341_RED);
                }
                if (z == 3) {
                  tft.drawRect(a2, b2, a - a2, b - b2, ILI9341_GREEN);
                }
                if (z == 4) {
                  tft.drawRect(a2, b2, a - a2, b - b2, ILI9341_CYAN);
                }
                if (z == 5) {
                  tft.drawRect(a2, b2, a - a2, b - b2, ILI9341_MAGENTA);
                }
                if (z == 6) {
                  tft.drawRect(a2, b2, a - a2, b - b2, ILI9341_YELLOW);
                }
                if (z == 7) {
                  tft.drawRect(a2, b2, a - a2, b - b2, ILI9341_WHITE);
                }
              }
              if (y4 == 1) {
                if (z == 0) {
                  tft.fillRect(a2, b2, a - a2, b - b2, ILI9341_BLACK);
                }
                if (z == 1) {
                  tft.fillRect(a2, b2, a - a2, b - b2, ILI9341_BLUE);
                }
                if (z == 2) {
                  tft.fillRect(a2, b2, a - a2, b - b2, ILI9341_RED);
                }
                if (z == 3) {
                  tft.fillRect(a2, b2, a - a2, b - b2, ILI9341_GREEN);
                }
                if (z == 4) {
                  tft.fillRect(a2, b2, a - a2, b - b2, ILI9341_CYAN);
                }
                if (z == 5) {
                  tft.fillRect(a2, b2, a - a2, b - b2, ILI9341_MAGENTA);
                }
                if (z == 6) {
                  tft.fillRect(a2, b2, a - a2, b - b2, ILI9341_YELLOW);
                }
                if (z == 7) {
                  tft.fillRect(a2, b2, a - a2, b - b2, ILI9341_WHITE);
                }
              }
            }
            if (a2 > a && b2 > b) {
              if (y4 == 0) {
                if (z == 0) {
                  tft.drawRect(a, b, a2 - a, b2 - b, ILI9341_BLACK);
                }
                if (z == 1) {
                  tft.drawRect(a, b, a2 - a, b2 - b, ILI9341_BLUE);
                }
                if (z == 2) {
                  tft.drawRect(a, b, a2 - a, b2 - b, ILI9341_RED);
                }
                if (z == 3) {
                  tft.drawRect(a, b, a2 - a, b2 - b, ILI9341_GREEN);
                }
                if (z == 4) {
                  tft.drawRect(a, b, a2 - a, b2 - b, ILI9341_CYAN);
                }
                if (z == 5) {
                  tft.drawRect(a, b, a2 - a, b2 - b, ILI9341_MAGENTA);
                }
                if (z == 6) {
                  tft.drawRect(a, b, a2 - a, b2 - b, ILI9341_YELLOW);
                }
                if (z == 7) {
                  tft.drawRect(a, b, a2 - a, b2 - b, ILI9341_WHITE);
                }
              }
              if (y4 == 1) {
                if (z == 0) {
                  tft.fillRect(a, b, a2 - a, b2 - b, ILI9341_BLACK);
                }
                if (z == 1) {
                  tft.fillRect(a, b, a2 - a, b2 - b, ILI9341_BLUE);
                }
                if (z == 2) {
                  tft.fillRect(a, b, a2 - a, b2 - b, ILI9341_RED);
                }
                if (z == 3) {
                  tft.fillRect(a, b, a2 - a, b2 - b, ILI9341_GREEN);
                }
                if (z == 4) {
                  tft.fillRect(a, b, a2 - a, b2 - b, ILI9341_CYAN);
                }
                if (z == 5) {
                  tft.fillRect(a, b, a2 - a, b2 - b, ILI9341_MAGENTA);
                }
                if (z == 6) {
                  tft.fillRect(a, b, a2 - a, b2 - b, ILI9341_YELLOW);
                }
                if (z == 7) {
                  tft.fillRect(a, b, a2 - a, b2 - b, ILI9341_WHITE);
                }
              }
            }
            if (a2 > a && b2 < b) {
              if (y4 == 0) {
                if (z == 0) {
                  tft.drawRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_BLACK);
                }
                if (z == 1) {
                  tft.drawRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_BLUE);
                }
                if (z == 2) {
                  tft.drawRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_RED);
                }
                if (z == 3) {
                  tft.drawRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_GREEN);
                }
                if (z == 4) {
                  tft.drawRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_CYAN);
                }
                if (z == 5) {
                  tft.drawRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_MAGENTA);
                }
                if (z == 6) {
                  tft.drawRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_YELLOW);
                }
                if (z == 7) {
                  tft.drawRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_WHITE);
                }
              }
              if (y4 == 1) {
                if (z == 0) {
                  tft.fillRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_BLACK);
                }
                if (z == 1) {
                  tft.fillRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_BLUE);
                }
                if (z == 2) {
                  tft.fillRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_RED);
                }
                if (z == 3) {
                  tft.fillRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_GREEN);
                }
                if (z == 4) {
                  tft.fillRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_CYAN);
                }
                if (z == 5) {
                  tft.fillRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_MAGENTA);
                }
                if (z == 6) {
                  tft.fillRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_YELLOW);
                }
                if (z == 7) {
                  tft.fillRect(a, b - (b - b2), a2 - a, b - b2, ILI9341_WHITE);
                }
              }
            }
            if (a2 < a && b2 > b) {
              if (y4 == 0) {
                if (z == 0) {
                  tft.drawRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_BLACK);
                }
                if (z == 1) {
                  tft.drawRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_BLUE);
                }
                if (z == 2) {
                  tft.drawRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_RED);
                }
                if (z == 3) {
                  tft.drawRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_GREEN);
                }
                if (z == 4) {
                  tft.drawRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_CYAN);
                }
                if (z == 5) {
                  tft.drawRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_MAGENTA);
                }
                if (z == 6) {
                  tft.drawRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_YELLOW);
                }
                if (z == 7) {
                  tft.drawRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_WHITE);
                }
              }
              if (y4 == 1) {
                if (z == 0) {
                  tft.fillRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_BLACK);
                }
                if (z == 1) {
                  tft.fillRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_BLUE);
                }
                if (z == 2) {
                  tft.fillRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_RED);
                }
                if (z == 3) {
                  tft.fillRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_GREEN);
                }
                if (z == 4) {
                  tft.fillRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_CYAN);
                }
                if (z == 5) {
                  tft.fillRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_MAGENTA);
                }
                if (z == 6) {
                  tft.fillRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_YELLOW);
                }
                if (z == 7) {
                  tft.fillRect(a - (a - a2), b, a - a2, b2 - b, ILI9341_WHITE);
                }
              }
            }
          }
        }
      }
      if (y3 == 2) {
        if (x < 294 && y > 35) {
          if (y6 == 0) {
            a = x;
            b = y;
            y6 = 1;
          }
          if (y6 == 1) {
            aa = a2;
            bb = b2;
            a2 = x;
            b2 = y;
            if (a + r < 294 && b - r > 35) {
              if (aa != a2 || bb != b2) {
                if (y4 == 0) {
                  tft.drawCircle(a, b, r, ILI9341_WHITE);
                }
                if (y4 == 1) {
                  tft.fillCircle(a, b, r, ILI9341_WHITE);
                }
              }
            }
            r = sqrt(square(a - a2) + square(b - b2));
            if (a + r < 294 && b - r > 35) {
              if (y4 == 0) {
                if (z == 0) {
                  tft.drawCircle(a, b, r, ILI9341_BLACK);
                }
                if (z == 1) {
                  tft.drawCircle(a, b, r, ILI9341_BLUE);
                }
                if (z == 2) {
                  tft.drawCircle(a, b, r, ILI9341_RED);
                }
                if (z == 3) {
                  tft.drawCircle(a, b, r, ILI9341_GREEN);
                }
                if (z == 4) {
                  tft.drawCircle(a, b, r, ILI9341_CYAN);
                }
                if (z == 5) {
                  tft.drawCircle(a, b, r, ILI9341_MAGENTA);
                }
                if (z == 6) {
                  tft.drawCircle(a, b, r, ILI9341_YELLOW);
                }
                if (z == 7) {
                  tft.drawCircle(a, b, r, ILI9341_WHITE);
                }
              }
              if (y4 == 1) {
                if (z == 0) {
                  tft.fillCircle(a, b, r, ILI9341_BLACK);
                }
                if (z == 1) {
                  tft.fillCircle(a, b, r, ILI9341_BLUE);
                }
                if (z == 2) {
                  tft.fillCircle(a, b, r, ILI9341_RED);
                }
                if (z == 3) {
                  tft.fillCircle(a, b, r, ILI9341_GREEN);
                }
                if (z == 4) {
                  tft.fillCircle(a, b, r, ILI9341_CYAN);
                }
                if (z == 5) {
                  tft.fillCircle(a, b, r, ILI9341_MAGENTA);
                }
                if (z == 6) {
                  tft.fillCircle(a, b, r, ILI9341_YELLOW);
                }
                if (z == 7) {
                  tft.fillCircle(a, b, r, ILI9341_WHITE);
                }
              }
            }
          }
        }
      }
      if (y3 == 3) {
        if (x < 294 && y > 35) {
          if (y6 == 0) {
            a = x;
            b = y;
            a1 = a;
            b1 = b;
            y6 = 1;
          }
          if (y6 == 1) {
            aa = a1;
            bb = b1;
            a1 = x;
            b1 = y;
          }
          if (aa != a1 || bb != b1) {
            tft.drawLine(a, b, aa, bb, ILI9341_WHITE);
          }
          if (z == 0) {
            tft.drawLine(a, b, a1, b1, ILI9341_BLACK);
          }
          if (z == 1) {
            tft.drawLine(a, b, a1, b1, ILI9341_BLUE);
          }
          if (z == 2) {
            tft.drawLine(a, b, a1, b1, ILI9341_RED);
          }
          if (z == 3) {
            tft.drawLine(a, b, a1, b1, ILI9341_GREEN);
          }
          if (z == 4) {
            tft.drawLine(a, b, a1, b1, ILI9341_CYAN);
          }
          if (z == 5) {
            tft.drawLine(a, b, a1, b1, ILI9341_MAGENTA);
          }
          if (z == 6) {
            tft.drawLine(a, b, a1, b1, ILI9341_YELLOW);
          }
          if (z == 7) {
            tft.drawLine(a, b, a1, b1, ILI9341_WHITE);
          }
          if (y8 == 0) {
            tft.drawLine(97, 0, 97, 35, ILI9341_BLACK);//radius
            tft.drawLine(200, 0, 200, 35, ILI9341_BLACK);//radius
            tft.drawLine(62, 0, 62, 35, ILI9341_BLACK);//слева
            tft.drawLine(27, 0, 27, 35, ILI9341_BLACK);//слева
            tft.drawLine(235, 0, 235, 35, ILI9341_BLACK);//справа
            tft.drawLine(270, 0, 270, 35, ILI9341_BLACK);//справа
            tft.drawLine(27, 35, 270, 35, ILI9341_BLACK);//основа сверху
            tft.drawLine(225, 10, 210, 25, ILI9341_BLACK);//линия сверху
            tft.drawRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
            tft.drawCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            tft.drawRoundRect (102, 5, 25, 25, 3, ILI9341_BLACK);//-
            tft.drawRoundRect (170, 5, 25, 25, 3, ILI9341_BLACK);//+
            y8 = 1;
          }
        }
      }
      if (x < 127 && x > 102 && y < 30 && y > 5) {//- сверху
        if (flag2 == 1) {
          tft.fillRoundRect (103, 6, 23, 23, 2, ILI9341_BLACK);
          tft.setTextColor(ILI9341_WHITE);  // Определяем цвет текста для вывода на дисплей
          tft.setTextSize(3);               // Определяем размер шрифта для вывода на дисплей
          tft.setCursor(107, 7);             // Определяем координаты верхнего левого угла области вывода
          tft.print("-");
          radius1 = radius;
          if (radius1 < 10) {
            x1 = 141;
          }
          if (radius1 == 10) {
            x1 = 132;
          }
          tft.setTextColor(ILI9341_WHITE);  // Определяем цвет текста для вывода на дисплей
          tft.setTextSize(3);               // Определяем размер шрифта для вывода на дисплей
          tft.setCursor(x1, 7);             // Определяем координаты верхнего левого угла области вывода
          tft.print(radius1);
          radius--;
          if (radius == 0) {
            radius = 1;
          }
          tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
          tft.setTextSize(3);               // Определяем размер шрифта для вывода на дисплей
          tft.setCursor(141, 7);             // Определяем координаты верхнего левого угла области вывода
          tft.print(radius);
          flag2 = 0;
        }
      }
      if (x < 195 && x > 170 && y < 30 && y > 5) {//+ сверху
        if (flag1 == 1) {
          tft.fillRoundRect (171, 6, 23, 23, 2, ILI9341_BLACK);
          tft.setTextColor(ILI9341_WHITE);  // Определяем цвет текста для вывода на дисплей
          tft.setTextSize(3);               // Определяем размер шрифта для вывода на дисплей
          tft.setCursor(175, 7);             // Определяем координаты верхнего левого угла области вывода
          tft.print("+");
          radius1 = radius;
          if (radius < 10) {
            x1 = 141;
          }
          if (radius == 10) {
            x1 = 132;
          }
          tft.setTextColor(ILI9341_WHITE);  // Определяем цвет текста для вывода на дисплей
          tft.setTextSize(3);               // Определяем размер шрифта для вывода на дисплей
          tft.setCursor(x1, 7);             // Определяем координаты верхнего левого угла области вывода
          tft.print(radius1);
          radius++;
          if (radius == 11) {
            radius = 10;
          }
          if (radius < 10) {
            x1 = 141;
          }
          if (radius == 10) {
            x1 = 132;
          }
          tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
          tft.setTextSize(3);               // Определяем размер шрифта для вывода на дисплей
          tft.setCursor(x1, 7);             // Определяем координаты верхнего левого угла области вывода
          tft.print(radius);
          flag1 = 0;
        }
      }
      if (x > 27 && x < 62 && y < 35) { //квадрат сверху
        if (y2 == 1) {
          if (y3 == 1) {
            y3 = 0;
            tft.fillRect(28, 0, 34, 35, ILI9341_WHITE);
            tft.fillRect(63, 0, 34, 35, ILI9341_WHITE);
            tft.fillRect(201, 0, 34, 35, ILI9341_WHITE);
            tft.drawLine(225, 10, 210, 25, ILI9341_BLACK);//линия сверху
            if (y4 == 0) {
              tft.drawRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
              tft.drawCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            }
            if (y4 == 1) {
              tft.fillRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
              tft.fillCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            }
          }
          else {
            y3 = 1;
            tft.fillRect(28, 0, 34, 35, ILI9341_CYAN);
            tft.fillRect(63, 0, 34, 35, ILI9341_WHITE);
            tft.fillRect(201, 0, 34, 35, ILI9341_WHITE);
            tft.drawLine(225, 10, 210, 25, ILI9341_BLACK);//линия сверху
            if (y4 == 0) {
              tft.drawRect(37, 10, 15, 15, ILI9341_WHITE);//квадрат сверху
              tft.drawCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            }
            if (y4 == 1) {
              tft.fillRect(37, 10, 15, 15, ILI9341_WHITE);//квадрат сверху
              tft.fillCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            }
          }
          y2 = 0;
        }
      }
      if (x > 62 && x < 97 && y < 35) { //круг сверху
        if (y2 == 1) {
          if (y3 == 2) {
            y3 = 0;
            tft.fillRect(28, 0, 34, 35, ILI9341_WHITE);
            tft.fillRect(63, 0, 34, 35, ILI9341_WHITE);
            tft.fillRect(201, 0, 34, 35, ILI9341_WHITE);
            tft.drawLine(225, 10, 210, 25, ILI9341_BLACK);//линия сверху
            if (y4 == 0) {
              tft.drawRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
              tft.drawCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            }
            if (y4 == 1) {
              tft.fillRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
              tft.fillCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            }
          }
          else {
            y3 = 2;
            tft.fillRect(28, 0, 34, 35, ILI9341_WHITE);
            tft.fillRect(63, 0, 34, 35, ILI9341_CYAN);
            tft.fillRect(201, 0, 34, 35, ILI9341_WHITE);
            tft.drawLine(225, 10, 210, 25, ILI9341_BLACK);//линия сверху
            if (y4 == 0) {
              tft.drawRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
              tft.drawCircle(79, 17, 8, ILI9341_WHITE);// круг сверху
            }
            if (y4 == 1) {
              tft.fillRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
              tft.fillCircle(79, 17, 8, ILI9341_WHITE);// круг сверху
            }
          }
          y2 = 0;
        }
      }
      if (x > 200 && x < 235 && y < 35) { //линия сверху
        if (y2 == 1) {
          if (y3 == 3) {
            y3 = 0;
            tft.fillRect(28, 0, 34, 35, ILI9341_WHITE);
            tft.fillRect(63, 0, 34, 35, ILI9341_WHITE);
            tft.fillRect(201, 0, 34, 35, ILI9341_WHITE);
            tft.drawLine(225, 10, 210, 25, ILI9341_BLACK);//линия сверху
            if (y4 == 0) {
              tft.drawRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
              tft.drawCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            }
            if (y4 == 1) {
              tft.fillRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
              tft.fillCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            }
          }
          else {
            y3 = 3;
            tft.fillRect(28, 0, 34, 35, ILI9341_WHITE);
            tft.fillRect(63, 0, 34, 35, ILI9341_WHITE);
            tft.fillRect(201, 0, 34, 35, ILI9341_CYAN);
            tft.drawLine(225, 10, 210, 25, ILI9341_WHITE);//линия сверху
            if (y4 == 0) {
              tft.drawRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
              tft.drawCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            }
            if (y4 == 1) {
              tft.fillRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
              tft.fillCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            }
          }
          y2 = 0;
        }
      }
      if (x > 235 && x < 270 && y < 35) { //закрашивание сверху
        if (y5 == 1) {
          if (y4 == 0) {
            y4 = 1;
          }
          else {
            y4 = 0;
          }
          if (y4 == 0) {
            tft.fillRect(236, 0, 34, 35, ILI9341_WHITE);
            if (y3 == 0) {
              tft.fillRect(38, 11, 13, 13, ILI9341_WHITE);//квадрат сверху
              tft.fillCircle(79, 17, 7, ILI9341_WHITE);// круг сверху
            }
            if (y3 == 1) {
              tft.fillRect(38, 11, 13, 13, ILI9341_CYAN);//квадрат сверху
              tft.fillCircle(79, 17, 7, ILI9341_WHITE);// круг сверху
              tft.drawRect(37, 10, 15, 15, ILI9341_WHITE);//квадрат сверху
            }
            if (y3 == 2) {
              tft.fillRect(38, 11, 13, 13, ILI9341_WHITE);//квадрат сверху
              tft.fillCircle(79, 17, 7, ILI9341_CYAN);// круг сверху
              tft.drawCircle(79, 17, 8, ILI9341_WHITE);// круг сверху
            }
            if (y3 == 3) {
              tft.fillRect(38, 11, 13, 13, ILI9341_WHITE);//квадрат сверху
              tft.fillCircle(79, 17, 7, ILI9341_WHITE);// круг сверху
            }
          }
          if (y4 == 1) {
            tft.fillRect(236, 0, 34, 35, ILI9341_CYAN);
            if (y3 == 0) {
              tft.fillRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
              tft.fillCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            }
            if (y3 == 1) {
              tft.fillRect(37, 10, 15, 15, ILI9341_WHITE);//квадрат сверху
              tft.fillCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            }
            if (y3 == 2) {
              tft.fillRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
              tft.fillCircle(79, 17, 8, ILI9341_WHITE);// круг сверху
            }
            if (y3 == 3) {
              tft.fillRect(37, 10, 15, 15, ILI9341_BLACK);//квадрат сверху
              tft.fillCircle(79, 17, 8, ILI9341_BLACK);// круг сверху
            }
          }
          y5 = 0;
        }
      }
    }
  }
}
