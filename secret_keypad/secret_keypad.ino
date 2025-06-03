#include <Wire.h>                     // библиотека для управления устройствами по I2C 
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>        // подключаем библиотеку для QAPASS 1602

LiquidCrystal_I2C LCD(0x27, 16, 2);

int x = 15;                           //положение
int z;                                //режимы работы
int z1;                               //обнуление
int count;                            //количество цифр в числе
long y;                               //число 1
long y1;                              //число 2
long y2;                              //Число для счета количества цифр в числе
char key1;                            //предыдущий знак
const byte ROWS = 4;                  //four rows
const byte COLS = 4;                  //four columns
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '/'},
  {'4', '5', '6', '*'},
  {'7', '8', '9', '-'},
  {'C', '0', '=', '+'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};    //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2};    //connect to the column pinouts of the keypad

Keypad kpd = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  LCD.init();                         // инициализация LCD дисплея
  LCD.backlight();                    // включение подсветки дисплея
  LCD.setCursor(15, 0);
  LCD.print(y);
}

void loop() {
  char Key = kpd.getKey();
  if (Key) {
    if (Key == 'C') {
      LCD.clear();
      z = 0;
      z1 = 0;
      x = 15;
      y = 0;
      y1 = 0;
      count = 0;
      LCD.setCursor(15, 0);
      LCD.print(y);
    }
    if (Key == '=') {
      LCD.clear();
      LCD.setCursor(15, 1);
      LCD.print("=");
      if (z > 1) {
        if (key1 == '/') {
          y = y / y1;
        }
        if (key1 == '*') {
          y = y * y1;
        }
        if (key1 == '-') {
          y = y - y1;
        }
        if (key1 == '+') {
          y = y + y1;
        }
      }
      if (key1 == '/' && y1 == 0) {
        LCD.clear();
        LCD.setCursor(11, 0);
        LCD.print("ERROR");
        z = 4;
      }
      if(y == 0){
          LCD.clear();
          LCD.setCursor(15, 1);
          LCD.print(Key);
          LCD.setCursor(15, 0);
          LCD.print(y);
          z = 4;
        }
      else {
        y2 = y;
        while (y2 > 0) {
          y2 /= 10;
          count++;
        }
        x = 15;
        LCD.setCursor(x - count + 1, 0);
        LCD.print(y);
        count = 0;
        z = 4;
      }
    }
    if (Key == '/') {
      LCD.setCursor(15, 1);
      LCD.print("/");
      z1 = 0;
      if (z == 0) {
        z = 1;
        key1 = Key;
      }
      if (z == 2) {
        z = 3;
      }
    }
    if (Key == '*') {
      LCD.setCursor(15, 1);
      LCD.print("*");
      z1 = 0;
      if (z == 0) {
        z = 1;
        key1 = Key;
      }
      if (z == 2) {
        z = 3;
      }
    }
    if (Key == '-') {
      LCD.setCursor(15, 1);
      LCD.print("-");
      z1 = 0;
      if (z == 0) {
        z = 1;
        key1 = Key;
      }
      if (z == 2) {
        z = 3;
      }
    }
    if (Key == '+') {
      LCD.setCursor(15, 1);
      LCD.print("+");
      z1 = 0;
      if (z == 0) {
        z = 1;
        key1 = Key;
      }
      if (z == 2) {
        z = 3;
        //key1 = Key;
      }
    }
    else {
      if (z == 0 && Key != 'C') {
        if (y * 10 + (Key - '0') < 1000000000) {
          y = y * 10 + (Key - '0');
          LCD.setCursor(x, 0);
          LCD.print(y);
          x--;
        }
      }

      if ((z == 2 || z == 1) && Key != 'C' && Key != '/' && Key != '*' && Key != '-' && Key != '+' && Key != '=') {
        //Serial.println(y1);
        if (z1 == 0) {
          LCD.clear();
          x = 15;
          y1 = 0;
          z1 = 1;
        }
        if (y1 * 10 + (Key - '0') < 1000000000) {
          y1 = y1 * 10 + (Key - '0');
          LCD.setCursor(x, 0);
          LCD.print(y1);
          z = 2;
          x--;
        }
      }

      if (z == 3) {
        if (key1 == '/') {
          y = y / y1;
        }
        if (key1 == '*') {
          y = y * y1;
        }
        if (key1 == '-') {
          y = y - y1;
        }
        if (key1 == '+') {
          y = y + y1;
        }
        if (key1 == '/' && y1 == 0) {
          LCD.clear();
          LCD.setCursor(11, 0);
          LCD.print("ERROR");
          z = 4;
        }
        if(y == 0){
          LCD.clear();
          LCD.setCursor(15, 1);
          LCD.print(Key);
          LCD.setCursor(15, 0);
          LCD.print(y);
          x = 15;
          count = 0;
          key1 = Key;
          y1 = 0;
          z = 1;
        }
        else {
          y2 = y;
          while (y2 > 0) {
            y2 /= 10;
            count++;
          }
          x = 15;
          LCD.clear();
          LCD.setCursor(15, 1);
          LCD.print(Key);
          LCD.setCursor(x - count + 1, 0);
          LCD.print(y);
          count = 0;
          key1 = Key;
          y1 = 0;
          z = 1;
        }
      }
    }
  }
}
