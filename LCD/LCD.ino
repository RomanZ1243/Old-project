#include <LiquidCrystal.h>

#include <LiquidCrystal_I2C.h> // подключаем библиотеку для QAPASS 1602
#include <Wire.h> // библиотека для управления устройствами по I2C 


LiquidCrystal_I2C LCD(0x27, 16, 2); // присваиваем имя LCD для дисплея

int r = 0;
int x = 100;
int y = -0;
int z = 1;
int a = 0;
byte  left1[8] = {
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000
};

byte  left2[8] = {
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000
};

byte  centre1[8] = {
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100
};

byte  right1[8] = {
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110
};

byte  right2[8] = {
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
  LCD.createChar(1, left1);
  LCD.createChar(2, left2);
  LCD.createChar(3, centre1);
  LCD.createChar(4, right1);
  LCD.createChar(5, right2); // ставим курсор на 1 символ первой строки
}



void loop() {
  if(a == 0){
     LCD.setCursor(0,0); // ставим курсор на 1 символ первой строки
     LCD.print("Loading...");    
     LCD.setCursor(10,0); // ставим курсор на 1 символ первой строки
     LCD.print(y = y + 1);
      if(y < 10){
      LCD.setCursor(11,0); // ставим курсор на 1 символ первой строки
     LCD.print("%");
     }
     if(y > 9){
      LCD.setCursor(12,0); // ставим курсор на 1 символ первой строки
     LCD.print("%");
     }
     if(y == 100){
      a = 1;
     }
     if(y > 19){
     LCD.setCursor(r,1); // ставим курсор на 1 символ первой строки
     LCD.print(char(z)); // печатаем символ на первой строке 
     delay(x);
     LCD.setCursor(10,0); // ставим курсор на 1 символ первой строки
     //LCD.print(y = y + 1);
     z = z + 1;
     if(z == 6){
      r = r + 1;
      z = 1;
      }     
    }
  }
  if(a == 1){
    LCD.setCursor(13,0); // ставим курсор на 1 символ первой строки
    LCD.print("%");
    LCD.setCursor(10,0); // ставим курсор на 1 символ первой строки
    LCD.print("100");
  }
}
