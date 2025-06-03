#include <GyverOLED.h>
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

int x;
int y;

void setup() {
  oled.init();        // инициализация
  oled.clear();
  oled.setScale(1);


}
void loop() {
  y = analogRead(A0);
  y = map(y, 0, 1023, 0, 63);
  oled.dot(x, y, 1);
  x++;
  delay(100);
  if(x == 129){
    oled.clear();
    x = 0;
  }
}
