/*
   M1 - выключить ленту
   M2 - включить ленту (включится последниэффект)
   M3 - эффект (радуга)
   M4 -
   M5 -
   M6 -
   M7 -
*/

#define NUM_LEDS 146
#define PIN_LED 3
#define RX 4
#define TX 5

#include <FastLED.h>
#include <SoftwareSerial.h>

CRGB leds[NUM_LEDS];
SoftwareSerial mySerial(RX, TX); // RX, TX

int val; //Данные с блютуз модуля
byte counter;

byte flag_bright;

void setup() {
  mySerial.begin(9600);
  FastLED.addLeds<WS2811, PIN_LED, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(50);
  pinMode(13, OUTPUT);
}
void loop() {
  switch (question()) {
    case '0':
      if (flag_bright == 0) {
        FastLED.setBrightness(0);
        flag_bright = 1;
      }
      break;
      case '1':
      if (flag_bright == 0) {
        FastLED.setBrightness(50);
        flag_bright = 1;
      }
      break;
  }
  /*if (Serial.available()) { // проверяем, поступают ли какие-то команды
    val = Serial.read(); // переменная val равна полученной команде
    if (val == '1') { //вставить нужные условия и эффекты для адресной ленты
      digitalWrite(13, HIGH);
    }
    }
    for (int i = 0; i < NUM_LEDS; i++ ) {         // от 0 до первой трети
    leds[i] = CHSV(counter + i * 2, 255, 255);  // HSV. Увеличивать HUE (цвет)
    // умножение i уменьшает шаг радуги
    }
    counter++;        // counter меняется от 0 до 255 (тип данных byte)*/
  FastLED.show();
  delay(5);         // скорость движения радуги
}

int question() {
  if (Serial.available()) { // проверяем, поступают ли какие-то команды
    val = Serial.read(); // переменная val равна полученной команде
  }
  return val;
}
