#include <GyverOLED.h>
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

int x;
int y;
int x1;
int y1;

void setup() {
  oled.init();        // инициализация
  oled.clear();
  oled.setScale(1);


}
void loop() {
  oled.clear();
  oled.line(0, y, 128, y, 1);
  oled.line(x, 0, x, 64, 1);
  delay(25);
  if (x1 == 0) {
    x++;
  }
  if (x1 == 1) {
    x--;
  }
  if (x == 0) {
    x1 = 0;
  }
  if (x == 127) {
    x1 = 1;
  }
  if (y1 == 0) {
    y++;
  }
  if (y1 == 1) {
    y--;
  }
  if (y == 0) {
    y1 = 0;
  }
  if (y == 63) {
    y1 = 1;
  }
}
