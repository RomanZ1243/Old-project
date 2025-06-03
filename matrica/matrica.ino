// Подключаем библиотеку Adafruit NeoPixel.
#include "Adafruit_NeoPixel.h"

// Указываем, какое количество пикселей у нашей ленты.
#define LED_COUNT 256

// Указываем, к какому порту подключен вход ленты DIN.
#define LED_PIN 6

// Создаем переменную strip для управления нашей лентой.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int x;
int r;
int g;
int b;

void setup()
{
  // Инициализируем ленту.
  strip.begin();
  strip.show();
}

void loop()
{
  // Включаем все светодиоды.
  for (int i = 0; i < LED_COUNT; i++)
  {
    if (i % 16 == 0) {
      if (x == 0) {
        r = r - 51;
        g = g + 51;
        b = 0;
        if (g == 255) {
          x = 1;
        }
      }
      if (x == 1) {
        g = g - 51;
        b = b + 51;
        r = 0;
        if (b == 255) {
          x = 2;
        }
      }
        if (x == 2) {
        b = b - 51;
        r = r + 51;
        g = 0;
        if (r == 255) {
          x = 0;
        }
      }
    }
    strip.setPixelColor(i, strip.Color(r, g, b)); // Красный цвет.
  }
  // Передаем цвета ленте.
  strip.show();
  // Ждем 500 мс.
  delay(100);
}
