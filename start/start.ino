#include <LiquidCrystal_I2C.h> // подключаем библиотеку для QAPASS 
#include <Wire.h> // библиотека для управления устройствами по I2C 
LiquidCrystal_I2C LCD(0x27,16,2); // присваиваем имя LCD для дисплея

byte strelka_1[8] = {
0b10000,
0b10000,
0b10000,
0b10000,
0b10000,
0b10000,
0b10000,
0b10000
};

byte strelka_2[8] = {
0b11000,
0b11000,
0b11000,
0b11000,
0b11000,
0b11000,
0b11000,
0b11000
};

byte strelka_3[8] = {
0b11100,
0b11100,
0b11100,
0b11100,
0b11100,
0b11100,
0b11100,
0b11100
};

byte strelka_4[8] = {
0b11110,
0b11110,
0b11110,
0b11110,
0b11110,
0b11110,
0b11110,
0b11110
};

byte strelka_5[8] = {
0b11111,
0b11111,
0b11111,
0b11111,
0b11111,
0b11111,
0b11111,
0b11111
};

void setup() {
  LCD.init(); // инициализация LCD дисплея
  LCD.backlight(); // включение подсветки дисплея
  LCD.createChar(1, strelka_1);
  LCD.createChar(2, strelka_2);
  LCD.createChar(3, strelka_3);
  LCD.createChar(4, strelka_4);
  LCD.createChar(5, strelka_5);
}

void loop() {
  LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
  LCD.print("Time");  // put your main code here, to run repeatedly:
  delay(1000);
  LCD.clear();
}
