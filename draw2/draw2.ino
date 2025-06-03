// Видеообзоры и уроки работы с ARDUINO на YouTube-канале IOMOIO: https://www.youtube.com/channel/UCmNXABaTjX_iKH28TTJpiqA

#include "Adafruit_GFX.h"     // Библиотека обработчика графики
#include "Adafruit_ILI9341.h" // Программные драйвера для дисплеев ILI9341
#include "URTouch.h"          // Библиотека для работы с сенсорным экраном

#define TFT_DC 9              // Пин подключения вывода D/C дисплея
#define TFT_CS 10             // Пин подключения вывода CS дисплея
// Для управления очисткой экрана с помощью кнопки RESET на Arduino подключить вывод  дисплея RESET через резистор к пину RESET на плате Arduino
// Для Mega 2560 вывод дисплея RESET, если не подключен в пин RESET на Arduino, подключить в 3.3V (без резистора), либо в 5V (с резистором)
#define TFT_RST 8             // Пин подключения вывода RESET (Если подключен к питанию или кнопке, то эту строку закомментировать, а следующую раскомментировать)
// #define TFT_RST -1         // Если вывод дисплея RESET подключен к питанию или через кнопку RESET на Arduino
// Uno Hardware SPI
#define TFT_MISO 12           // Пин подключения вывода дисплея SDO(MISO)
#define TFT_MOSI 11           // Пин подключения вывода дисплея SDI(MOSI)
#define TFT_CLK 13            // Пин подключения вывода дисплея SCK

int x;
int y;

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

void setup() {
  tft.begin();                      // Инициализируем начало работы с графическим дисплеем
  tft.setRotation(2);               // Переводим дисплей в альбомную ориентацию

  ts.InitTouch();                   // Инициализируем сенсорный модуль дисплея
  ts.setPrecision(PREC_EXTREME);
  Serial.begin(9600);// Определяем необходимую точность обработки нажатий: PREC_LOW - низкая, PREC_MEDIUM - средняя, PREC_HI - высокая, PREC_EXTREME - максимальная
  tft.fillScreen(ILI9341_WHITE);
  //tft.drawRect(293, 0, 27, 227, ILI9341_BLACK);
  tft.drawLine(0, 240, 240, 240, ILI9341_BLACK);
  tft.drawLine(0, 160, 240, 160, ILI9341_BLACK);
  tft.drawLine(0, 80, 240, 80, ILI9341_BLACK);
  tft.drawLine(80, 80, 80, 320, ILI9341_BLACK);
  tft.drawLine(160, 80, 160, 320, ILI9341_BLACK);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(30, 105);             // Определяем координаты верхнего левого угла области вывода
  tft.print(1);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(110, 105);             // Определяем координаты верхнего левого угла области вывода
  tft.print(2);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(190, 105);             // Определяем координаты верхнего левого угла области вывода
  tft.print(3);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(30, 185);             // Определяем координаты верхнего левого угла области вывода
  tft.print(4);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(110, 185);             // Определяем координаты верхнего левого угла области вывода
  tft.print(5);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(190, 185);             // Определяем координаты верхнего левого угла области вывода
  tft.print(6);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(30, 265);             // Определяем координаты верхнего левого угла области вывода
  tft.print(7);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(110, 265);             // Определяем координаты верхнего левого угла области вывода
  tft.print(8);
  tft.setTextColor(ILI9341_BLACK);  // Определяем цвет текста для вывода на дисплей
  tft.setTextSize(4);               // Определяем размер шрифта для вывода на дисплей
  tft.setCursor(190, 265);             // Определяем координаты верхнего левого угла области вывода
  tft.print(9);
  /*
    tft.setTextColor(ILI9341_WHITE);  // Определяем цвет текста для вывода на дисплей
    tft.setTextSize(2);               // Определяем размер шрифта для вывода на дисплей
    tft.setCursor(55,5);              // Определяем координаты верхнего левого угла области вывода
    tft.print(utf8rus("Тестируем") + " TouchTFT");  // Выводим текст; Функция utf8rus конвертирует текст в русский, если библиотека Adafruit_GFX оптимизирована для работы с кириллицей
    tft.setTextColor(ILI9341_GREEN);  // Определяем цвет текста для вывода на экран
    tft.setCursor(20,220);            // Определяем координаты верхнего левого угла области вывода
    tft.print("http://iomoio.ru");
  */// Выводим текст
}

void loop()
{ // Переменные для работы с координатами нажатий
  while (ts.dataAvailable())        // Пока имеются данные с сенсорного модуля
  {

    //int radius = 4;               // Определяем радиус разрисовки
    //tft.fillCircle(x, y, radius, ILI9341_YELLOW); // Рисуем окружность, закрашенную желтым
  }
}
// Начало функции обработки кириллических символов
/*String utf8rus(String source)  // Функция для конвертации русских символов из двубайтовой кодировки в однобайтовую
  {
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };
  k = source.length(); i = 0;
  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xBF){
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x2F;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB7; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x6F;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
  return target;
  }*/
// Конец функции обработки кириллических символов
