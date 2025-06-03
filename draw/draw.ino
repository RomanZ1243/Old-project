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

int radius = 4;
int z;

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
{
  int x, y;                         // Переменные для работы с координатами нажатий

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
      Serial.println(x);
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
          tft.fillRect(0, 0, 294, 240, ILI9341_WHITE);
        }
      }
      if (0 < x && x < 290){
        if(z == 0){
          tft.fillCircle(x, y, radius, ILI9341_BLACK);
        }
        if(z == 1){
          tft.fillCircle(x, y, radius, ILI9341_BLUE);
        }
        if(z == 2){
          tft.fillCircle(x, y, radius, ILI9341_RED);
        }
        if(z == 3){
          tft.fillCircle(x, y, radius, ILI9341_GREEN);
        }
        if(z == 4){
          tft.fillCircle(x, y, radius, ILI9341_CYAN);
        }
        if(z == 5){
          tft.fillCircle(x, y, radius, ILI9341_MAGENTA);
        }
        if(z == 6){
          tft.fillCircle(x, y, radius, ILI9341_YELLOW);
        }
        if(z == 7){
          tft.fillCircle(x, y, radius, ILI9341_WHITE);
        }
      }
    }
    // Корректируем координату с учетом калибровочных данных
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
