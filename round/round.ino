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

int x1;
int y1;
int a;
int r;

void setup(){
  Serial.begin(9600);
  tft.begin();                      // Инициализируем начало работы с графическим дисплеем
  tft.setRotation(1);               // Переводим дисплей в альбомную ориентацию
 
  ts.InitTouch();                   // Инициализируем сенсорный модуль дисплея 
  ts.setPrecision(PREC_EXTREME);    // Определяем необходимую точность обработки нажатий: PREC_LOW - низкая, PREC_MEDIUM - средняя, PREC_HI - высокая, PREC_EXTREME - максимальная

  tft.drawCircle(160, 120, 80, ILI9341_BLACK);
  a = 45;
  r = 80;
  x1 = cos(radians(a)) * r + 160;
  y1 = sin(radians(a)) * r + 120;
  Serial.println(x1);//-1
  Serial.println(y1);//2
  tft.fillCircle(x1, y1, 3, ILI9341_YELLOW);// Выводим текст
  /*tft.fillCircle(cos(45) * 80 + 160, sin(45) * 80 + 120, 3, ILI9341_YELLOW);
  tft.fillCircle(cos(90) * 80 + 160, sin(90) * 80 + 120, 3, ILI9341_YELLOW);
  tft.fillCircle(cos(135) * 80 + 160, sin(135) * 80 + 120, 3, ILI9341_YELLOW);
  tft.fillCircle(cos(180) * 80 + 160, sin(180) * 80 + 120, 3, ILI9341_YELLOW);
  tft.fillCircle(cos(225) * 80 + 160, sin(225) * 80 + 120, 3, ILI9341_YELLOW);*/
  /*tft.fillCircle(cos(150) * 80 + 160, sin(150) * 80 + 120, 3, ILI9341_YELLOW);
  tft.fillCircle(cos(180) * 80 + 160, sin(180) * 80 + 120, 3, ILI9341_YELLOW);
  tft.fillCircle(cos(210) * 80 + 160, sin(210) * 80 + 120, 3, ILI9341_YELLOW);
  tft.fillCircle(cos(240) * 80 + 160, sin(240) * 80 + 120, 3, ILI9341_YELLOW);*/
}
 
void loop()
{
  /*int x, y;                         // Переменные для работы с координатами нажатий
 
  while(ts.dataAvailable())         // Пока имеются данные с сенсорного модуля
  {
    ts.read();                      // Считываем с него данные
    x = ts.getX();                  // Считываем координату нажатия X
    y = ts.getY();                  // Считываем координату нажатия Y
    if((x!=-1) && (y!=-1))          // Если обе координаты в положительном диапазоне (т.е. если есть нажатие)
    {
      x += 13;                      // Корректируем координату с учетом калибровочных данных
      y += 4;                       // Корректируем координату с учетом калибровочных данных
      int radius = 4;               // Определяем радиус разрисовки
      tft.fillCircle(x, y, radius, ILI9341_YELLOW); // Рисуем окружность, закрашенную желтым 
    }
  }*/
}
