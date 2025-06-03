#include "Adafruit_GFX.h"     // Библиотека обработчика графики
#include "Adafruit_ILI9341.h" // Программные драйвера для дисплеев ILI9341
#include "URTouch.h"          // Библиотека для работы с сенсорным экраном

#define TFT_DC 9              // Пин подключения вывода D/C дисплея
#define TFT_CS 10             // Пин подключения вывода CS дисплея
#define TFT_RST 8             // Пин подключения вывода RESET (Если подключен к питанию или кнопке, то эту строку закомментировать, а следующую раскомментировать)
#define TFT_MISO 12           // Пин подключения вывода дисплея SDO(MISO)
#define TFT_MOSI 11           // Пин подключения вывода дисплея SDI(MOSI)
#define TFT_CLK 13            // Пин подключения вывода дисплея SCK

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);  // Создаем объект дисплея и сообщаем библиотеке распиновку для работы с графикой

#define t_SCK 3               // Пин подключения вывода дисплея T_CLK
#define t_CS 4                // Пин подключения вывода дисплея T_CS
#define t_MOSI 5              // Пин подключения вывода дисплея T_DIN
#define t_MISO 6              // Пин подключения вывода дисплея T_DOUT
#define t_IRQ 7               // Пин подключения вывода дисплея T_IRQ

URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ); // Создаем объект сенсорного модуля и сообщаем библиотеке распиновку для работы с ним

int x1;
int y1;
int steps = 4;


void setup() {
  tft.begin();                      // Инициализируем начало работы с графическим дисплеем
  tft.setRotation(1);               // Переводим дисплей в альбомную ориентацию
  ts.InitTouch();                   // Инициализируем сенсорный модуль дисплея
  ts.setPrecision(PREC_EXTREME);
  Serial.begin(9600);// Определяем необходимую точность обработки нажатий: PREC_LOW - низкая, PREC_MEDIUM - средняя, PREC_HI - высокая, PREC_EXTREME - максимальная
  tft.fillScreen(ILI9341_WHITE);
  tft.drawLine(40, 20, 200, 20, ILI9341_BLACK);//горизонтальные линии
  tft.drawLine(40, 40, 200, 40, ILI9341_BLACK);
  tft.drawLine(40, 60, 200, 60, ILI9341_BLACK);
  tft.drawLine(40, 80, 200, 80, ILI9341_BLACK);
  tft.drawLine(0, 100, 200, 100, ILI9341_BLACK);
  tft.drawLine(40, 120, 200, 120, ILI9341_BLACK);
  tft.drawLine(40, 140, 200, 140, ILI9341_BLACK);
  tft.drawLine(40, 160, 200, 160, ILI9341_BLACK);
  tft.drawLine(40, 180, 200, 180, ILI9341_BLACK);
  tft.drawLine(40, 200, 200, 200, ILI9341_BLACK);
  tft.drawLine(40, 220, 200, 220, ILI9341_BLACK);
  tft.drawLine(40, 0, 40, 240, ILI9341_BLACK);
  tft.fillRect(10, 20, 30, 20, ILI9341_BLACK);//клавиши
  tft.fillRect(10, 60, 30, 20, ILI9341_BLACK);
  tft.fillRect(10, 120, 30, 20, ILI9341_BLACK);
  tft.fillRect(10, 160, 30, 20, ILI9341_BLACK);
  tft.fillRect(10, 200, 30, 20, ILI9341_BLACK);
  tft.drawLine(0, 30, 40, 30, ILI9341_BLACK);
  tft.drawLine(0, 70, 40, 70, ILI9341_BLACK);
  tft.drawLine(0, 130, 40, 130, ILI9341_BLACK);
  tft.drawLine(0, 170, 40, 170, ILI9341_BLACK);
  tft.drawLine(0, 210, 40, 210, ILI9341_BLACK);
  tft.drawLine(60, 0, 60, 240, ILI9341_BLACK);//вертикальные линии
  tft.drawLine(80, 0, 80, 240, ILI9341_BLACK);
  tft.drawLine(100, 0, 100, 240, ILI9341_BLACK);
  tft.drawLine(120, 0, 120, 240, ILI9341_BLACK);
  tft.drawLine(140, 0, 140, 240, ILI9341_BLACK);
  tft.drawLine(160, 0, 160, 240, ILI9341_BLACK);
  tft.drawLine(180, 0, 180, 240, ILI9341_BLACK);
  tft.drawLine(180, 0, 180, 240, ILI9341_BLACK);
  tft.drawLine(200, 0, 200, 240, ILI9341_BLACK);
  tft.fillRect(201, 0, 59, 60, ILI9341_GREEN);
  tft.fillRect(261, 0, 59, 60, ILI9341_GREEN);
  tft.drawLine(200, 60, 320, 60, ILI9341_BLACK);
  tft.drawLine(260, 0, 260, 60, ILI9341_BLACK);
  tft.drawLine(200, 120, 320, 120, ILI9341_BLACK);
  tft.drawLine(200, 180, 320, 180, ILI9341_BLACK);
  tft.drawLine(260, 180, 260, 240, ILI9341_BLACK);
  tft.fillRect(284, 20, 4, 20, ILI9341_BLACK);
  tft.fillRect(294, 20, 4, 20, ILI9341_BLACK);
  tft.fillTriangle(221, 20, 221, 40, 241, 30, ILI9341_BLACK);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(250, 76);              // Определяем координаты верхнего левого угла области вывода
  tft.print(steps);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(226, 136);              // Определяем координаты верхнего левого угла области вывода
  tft.print(steps);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(250, 136);              // Определяем координаты верхнего левого угла области вывода
  tft.print("/");
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(274, 136);              // Определяем координаты верхнего левого угла области вывода
  tft.print(steps);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(221, 197);              // Определяем координаты верхнего левого угла области вывода
  tft.print("-");
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(281, 197);              // Определяем координаты верхнего левого угла области вывода
  tft.print("+");
}

void loop() {
  /*int x, y;                         // Переменные для работы с координатами нажатий

  while (ts.dataAvailable())        // Пока имеются данные с сенсорного модуля
  {
    ts.read();                      // Считываем с него данные
    x = ts.getX();                  // Считываем координату нажатия X
    y = ts.getY();                  // Считываем координату нажатия Y
    if ((x != -1) && (y != -1))     // Если обе координаты в положительном диапазоне (т.е. если есть нажатие)
    {
      x += 13;                      // Корректируем координату с учетом калибровочных данных
      y += 4;                       // Корректируем координату с учетом калибровочных данных
    }
    //x1 = 
  }*/
}
