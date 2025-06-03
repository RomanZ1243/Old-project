
//#include <LiquidCrystal.h>

#include <LiquidCrystal_I2C.h> // подключаем библиотеку для QAPASS 1602
#include <Wire.h> // библиотека для управления устройствами по I2C 
LiquidCrystal_I2C LCD(0x27, 16, 2); // присваиваем имя LCD для дисплея

int x;
int x1 = -1;
int x2 = -1;
int x3 = -1;
int x4 = -1;
int x5;
int x6 = 100;// delay();
int a1;
int a2;
int a3;
int a4;
int a5;
int y;
int y1 = 1;
int y2 = 2;
int y3 = 1;
int y4;
int y5;
int xx;

byte  dino1[8] = {
  0b01110,
  0b10111,
  0b11111,
  0b10000,
  0b11111,
  0b11110,
  0b10011,
  0b11000
};

byte  dino2[8] = {
  0b01110,
  0b10111,
  0b11111,
  0b10000,
  0b11111,
  0b11110,
  0b11010,
  0b00011
};

byte  dino3[8] = {
  0b01110,
  0b10111,
  0b11111,
  0b10000,
  0b11111,
  0b11110,
  0b11011,
  0b00000
};

byte  cactus[8] = {
  0b00100,
  0b10100,
  0b10101,
  0b11101,
  0b00111,
  0b00100,
  0b00100,
  0b00100
};


void setup() {
  pinMode(2,INPUT_PULLUP);
  LCD.init(); // инициализация LCD дисплея
  LCD.backlight(); // включение подсветки дисплея
  LCD.createChar(1, dino1);// put your setup code here, to run once:
  LCD.createChar(2, dino2);
  LCD.createChar(3, dino3);
  LCD.createChar(4, cactus);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
if(y == 0){
  LCD.setCursor(6,0);
  LCD.print("Start");
if(digitalRead(2) == 0){
  LCD.clear();
  y = 1;
  }
}
 
if(y == 1){
if(y5 == 1){
  if(digitalRead(2) == 1 || y4 > 5){
  y1 = 1;
  y2 = 2;
  y3 = 1;
  y4 = 0;
  y5 = 0;
}

if(digitalRead(2) == 0){
  y1 = 3;
  y2 = 3;
  y3 = 0;
  y4++;
}
}
  if(a5 == 0){
     a1 = random(0, 3);
     a2 = random(6, 9);
     a3 = random(12, 15);
     a4 = random(18, 21);  
     a5 = 5;  
  }
  
  if(a5 == 1){
     a1 = random(0, 3);
     a5 = 5;  
  }
  if(a5 == 2){
    a2 = random(6, 9);
    a5 = 5;  
  }
  if(a5 == 3){
    a3 = random(12, 11);
    a5 = 5;  
  }
  if(a5 == 4){
    a4 = random(12, 15);
    a5 = 5;  
  }

  if(x == 0){
    a5 = 0;
  }
  
  
  LCD.setCursor(15 - x1,1);
  LCD.print(char(4));
  LCD.setCursor(15 - x2,1);
  LCD.print(char(4));
  LCD.setCursor(15 - x3,1);
  LCD.print(char(4));
  LCD.setCursor(15 - x4,1);
  LCD.print(char(4));
  x++;
  LCD.setCursor(11,0);
  LCD.print(x5++);
  LCD.setCursor(0,y3);
  LCD.print(char(y1));
  delay(x6);
  LCD.setCursor(0,y3);
  LCD.print(char(y2));
  delay(x6);
  if(y5 == 0){
    y5 = 1;
  }

  
  if(x % 5 == 0 && x6 > 50){
    x6--;
  }

  if(x > a1){
    LCD.clear();
    x1++;
  }
  
  if(x > a2){
    x2++;
  }

  if(x > a3){
    x3++; 
  }

  if(x > a4){
    x4++; 
  }
  
  if(x1 == 16){
    LCD.setCursor(0,1);
    LCD.print(" ");
    x1 = random(-3, 0);
  }

  if(x2 == 16){
    LCD.setCursor(0,1);
    LCD.print(" ");
    x2 = random(-2, 0);
  }

  if(x3 == 16){
    LCD.setCursor(0,1);
    LCD.print(" ");
    x3 = random(-1, 0);
  }

  if(x4 == 16){
    LCD.setCursor(0,1);
    LCD.print(" ");
    x4 = 0;
  } 

  if(y3 == 1 && x1 == 15){
     y = 2;
  }
  if(y3 == 1 && x2 == 15){
     y = 2;
  }
  if(y3 == 1 && x3 == 15){
     y = 2;
  }
  if(y3 == 1 && x4 == 15){
     y = 2;
  }
  if(y3 == 0 && x1 == !15){
     y = 1;
  }
  if(y3 == 0 && x2 == !15){
     y = 1;
  }
  if(y3 == 0 && x3 == !15){
     y = 1;
  }
  if(y3 == 0 && x4 == !15){
     y = 1;
  }
  
}

if(y == 2){
  LCD.clear();
  y = 3;
}


if(y == 3){
  if(x > xx){
  xx = x;
  LCD.setCursor(3,0);
  LCD.print("new record");
  delay(500);
  LCD.clear();
  delay(500);
  LCD.setCursor(3,0);
  LCD.print("new record");
  delay(500);
  LCD.clear();
  delay(500);
  LCD.setCursor(2,1);
  LCD.print(x);
  }
  else{
  LCD.setCursor(2,1);
  LCD.print(xx);  
  }
  LCD.setCursor(11,1);
  LCD.print(x);
  LCD.setCursor(3,0);
  LCD.print("Game over");
  if(digitalRead(2) == 0){
  x = 0;
  x1 = -1;
  x2 = -1;
  x3 = -1;
  x4 = -1;
  x5 = 0;
  x6 = 100;// delay();
  a5 = 0;
  y1 = 1;
  y2 = 2;
  y3 = 1;
  y4 = 0;
  y5 = 0;
  LCD.clear();
  y = 1;
  }
}
}
