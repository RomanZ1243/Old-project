// Видеообзоры и уроки работы с ARDUINO на YouTube-канале IOMOIO: https://www.youtube.com/channel/UCmNXABaTjX_iKH28TTJpiqA

#include "Adafruit_GFX.h"     // Библиотека обработчика графики
#include "Adafruit_ILI9341.h" // Программные драйвера для дисплеев ILI9341
#include "URTouch.h"          // Библиотека для работы с сенсорным экраном

#define TFT_DC 9              // Пин подключения вывода D/C дисплея
#define TFT_CS 10             // Пин подключения вывода CS дисплея
// Для управления очисткой экрана с помощью кнопки RESET на Arduino подключить вывод дисплея RESET через резистор к пину RESET на плате Arduino
// Для Mega 2560 вывод дисплея RESET, если не подключен в пин RESET на Arduino, подключить в 3.3V (без резистора), либо в 5V (с резистором)
#define TFT_RST 8             // Пин подключения вывода RESET (Если подключен к питанию или кнопке, то эту строку закомментировать, а следующую раскомментировать)
// #define TFT_RST -1         // Если вывод дисплея RESET подключен к питанию или через кнопку RESET на Arduino
// Uno Hardware SPI
#define TFT_MISO 12           // Пин подключения вывода дисплея SDO(MISO)
#define TFT_MOSI 11           // Пин подключения вывода дисплея SDI(MOSI)
#define TFT_CLK 13            // Пин подключения вывода дисплея SCK
/*
  //  Mega 2560 Hardware SPI
  #define TFT_MOSI 51           // Пин подключения вывода дисплея SDI(MOSI)
  #define TFT_CLK 52            // Пин подключения вывода дисплея SCK
  #define TFT_MISO 50           // Пин подключения вывода дисплея SDO(MISO)
*/


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);  // Создаем объект дисплея и сообщаем библиотеке распиновку для работы с графикой

#define t_SCK 3               // Пин подключения вывода дисплея T_CLK
#define t_CS 4                // Пин подключения вывода дисплея T_CS
#define t_MOSI 5              // Пин подключения вывода дисплея T_DIN
#define t_MISO 6              // Пин подключения вывода дисплея T_DOUT
#define t_IRQ 7               // Пин подключения вывода дисплея T_IRQ

URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ); // Создаем объект сенсорного модуля и сообщаем библиотеке распиновку для работы с ним

int x;
int y;
int radius = 4;
int point_x[] = {};//масив значений x
int point_y[] = {};//масив значений y
int a;//номер значения
int flag;//вывод значения

void setup() {
  Serial.begin(9600);
  tft.begin();                      // Инициализируем начало работы с графическим дисплеем
  tft.setRotation(1);               // Переводим дисплей в альбомную ориентацию
  tft.fillScreen(ILI9341_WHITE);
  ts.InitTouch();                   // Инициализируем сенсорный модуль дисплея
  ts.setPrecision(PREC_EXTREME);    // Определяем необходимую точность обработки нажатий: PREC_LOW - низкая, PREC_MEDIUM - средняя, PREC_HI - высокая, PREC_EXTREME - максимальная  // Выводим текст
  pinMode(2, INPUT_PULLUP);
}

void loop()
{
  /*if (digitalRead(2) == 0) {

    }*/// Переменные для работы с координатами нажатий
  if (digitalRead(2) == 0) {
    tft.fillScreen(ILI9341_WHITE);
    flag = 1;
  }
  if (flag == 1) {
    for (int i = 0; a + 1 > i; i++) {
      //Serial.println(point_x[i]);
      //Serial.println(point_y[i]);
      tft.fillCircle(point_x[i], point_y[i], radius, ILI9341_BLACK);
    }
  }

  while (ts.dataAvailable())        // Пока имеются данные с сенсорного модуля
  {
    ts.read();                      // Считываем с него данные
    x = ts.getX();                  // Считываем координату нажатия X
    y = ts.getY();

    if ((x != -1) && (y != -1))     // Если обе координаты в положительном диапазоне (т.е. если есть нажатие)
    {
      x = 320 - x;
      y = 240 - y;// Считываем координату нажатия Y
      //x += 13;                      // Корректируем координату с учетом калибровочных данных
      //y += 4;                       // Корректируем координату с учетом калибровочных данных             // Определяем радиус разрисовки
      tft.fillCircle(x, y, radius, ILI9341_BLACK); // Рисуем окружность, закрашенную желтым
      point_x[a] = x;
      point_y[a] = y;
      Serial.println(point_x[a]);
      Serial.println(point_y[a]);
      a++;
    }
  }
}
