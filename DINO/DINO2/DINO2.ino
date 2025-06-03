#include <LiquidCrystal_I2C.h> // подключаем библиотеку для QAPASS 1602
#include <Wire.h> // библиотека для управления устройствами по I2C 
LiquidCrystal_I2C LCD(0x27, 16, 2); // присваиваем имя LCD для дисплея

int y;//основа
volatile int y1;//выбор игрока
int y2;//время
int y3;//пробелы
int y4;//счетчик
int y5;
boolean z;//расположение игрока
int z1;//рандом
int z2;//рандом
int z3;//рандом
int z4;//рандом
int x;
int x1 = 16;//движение препядствий
int x2 = 20;//движение препядствий
int x3 = 24;//движение препядствий
int x4 = 28;//движение препядствий

byte man1[8] = {
  0b01110,
  0b10111,
  0b11111,
  0b10000,
  0b11111,
  0b11110,
  0b10011,
  0b11000
};

byte man2[8] = {
  0b01110,
  0b10111,
  0b11111,
  0b10000,
  0b11111,
  0b11110,
  0b11010,
  0b00011
};

byte man3[8] = {
  0b11000,
  0b10011,
  0b11110,
  0b11111,
  0b10000,
  0b11111,
  0b10111,
  0b01110
};

byte man4[8] = {
  0b00011,
  0b11001,
  0b11110,
  0b11111,
  0b10000,
  0b11111,
  0b10111,
  0b01110
};

byte car[8] = {
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110
};

void setup() {
  pinMode(2,INPUT_PULLUP);
  LCD.init(); // инициализация LCD дисплея
  LCD.backlight(); // включение подсветки дисплея
  LCD.createChar(1, man1);// put your setup code here, to run once:
  LCD.createChar(2, man2);
  LCD.createChar(3, man3);
  LCD.createChar(4, man4);
  LCD.createChar(5, car);
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
  if(x == 0){
    z1 = random(0, 2);
    z2 = random(0, 2);
    z3 = random(0, 2);
    z4 = random(0, 2);
    x = 1;
  }
  LCD.setCursor(x1,z1);
  LCD.print(char(5));
  LCD.setCursor(x2,z2);
  LCD.print(char(5));
  LCD.setCursor(x3,z3);
  LCD.print(char(5));
  LCD.setCursor(x4,z4);
  LCD.print(char(5));
  x1--;
  x2--;
  x3--;
  x4--;
  if(digitalRead(2) == 0){
  z = !z;
  if(z == 1){
    y1 = 1;
    
  }
  if(z == 0){
    y1 = 3;   
  }
  }
  LCD.setCursor(0,z);
  LCD.print(char(y1));
  delay(250);
  LCD.setCursor(0,z);
  LCD.print(char(y1 + 1));
  delay(250);
  y4++;
  LCD.clear();

  if(x1 < 0){
    x1 = 15;
    z1 = random(0, 2);
  }
  if(x2 < 0){
    x2 = 15;
    z2 = random(0, 2);
  }
  if(x3 < 0){
    x3 = 15;
    z3 = random(0, 2);
  }
  if(x4 < 0){
    x4 = 15;
    z4 = random(0, 2);
  }

  if(x1 == 0 || x2 == 0 || x3 == 0 || x4 == 0 && z == z1 || z == z2 || z == z3 || z == z4){
    y = 2;
}
}

if(y == 2){
  if(y4 > y5){
  y5 = y4;
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
  LCD.print(y4);
  }
  else{
  LCD.setCursor(2,1);
  LCD.print(y5);  
  }
  LCD.setCursor(11,1);
  LCD.print(y4);
  LCD.setCursor(3,0);
  LCD.print("Game over");
  if(digitalRead(2) == 0){
  volatile int y1;//выбор игрока
y2 = 0;//время
y3 = 0;//пробелы
y4 = 0;//счетчик
z = 0;//расположение игрока
x = 0;
x1 = 16;//движение препядствий
x2 = 20;//движение препядствий
x3 = 24;//движение препядствий
x4 = 28;//движение препядствий
y = 1;
  }
}
}
