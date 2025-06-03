#include "TimerOne.h"
#define d1 2
#define d2 3
#define d3 4
#define d4 5
#define a 6
#define b 7
#define c 8
#define d 9
#define e 10
#define f 11
#define g 12
#define DP 13
#define kn1 A0//кнопка выбора объекта //кнопка изменения времени
#define kn2 A1//кнопка выбора значения //кнопка запуска будильника
#define zum A2//пищалка

#include <GyverButton.h>
GButton butt1(kn1);//кнопка выбора объекта //кнопка изменения времени
GButton butt2(kn2);//кнопка выбора значения //кнопка запуска будильника

unsigned long timing;//моргание точек(для millis)
unsigned long timing2;//моргание точек(для millis)
//int x = 500;//моргание точек(для millis)
int h1;//часы левый символ(1)
int h2;//часы второй символ(2)
int m1;//минуты первый символ(3)
int m2;//минуты второй символ(4)
int y = 4;//задержка после case
int y1 = 100;//задержка для заставки
bool z;
int x1;
int x2;
long n = 0;
int x = 100;
int count = 0;
 
void setup() {
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(DP, OUTPUT);
  pinMode(zum, OUTPUT);//пищалка
  Serial.begin(9600);
  Timer1.initialize(100000);
  Timer1.attachInterrupt( add );
}


/*void loop() {
   digitalWrite(d1, LOW); // включаем первый разряд
   digitalWrite(d4, HIGH);
   delay(200);
   digitalWrite(d2, LOW); // включаем второй разряд
   digitalWrite(d1, HIGH);
   delay(200);
   digitalWrite(d3, LOW); // включаем третий разряд
   digitalWrite(d2, HIGH);
   delay(200);
   digitalWrite(d4, LOW); // включаем четвертый разряд
   digitalWrite(d3, HIGH);
   delay(200);
}*/
void loop() {
  while (digitalRead(A0) == LOW) {
    clearLEDs();
    pickDigit(0); // включаем первую цифру (тысячи)
    pickNumber((n / 1000));
    delay(5);

    clearLEDs();
    pickDigit(1); // включаем вторую цифру (сотни)
    pickNumber((n % 1000) / 100);
    delay(5);

    clearLEDs();
    pickDigit(2); // включаем третью цифру (десятки)
    pickNumber(n % 100 / 10);
    delay(5);

    clearLEDs();
    pickDigit(3); // включаем четвертую цифру (единицы)
    pickNumber(n % 10);
    delay(5);
  }
  if (digitalRead(A0) == HIGH) { n = 0; count = 0; }
}

// определение разряда
void pickDigit(int x) {
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  switch (x) {
    case 0: digitalWrite(d1, LOW);  break;
    case 1: digitalWrite(d2, LOW);  break;
    case 2: digitalWrite(d3, LOW);  break;
    default: digitalWrite(d4, LOW); break;
  }
}

// определение символа (цифры)
void pickNumber(int x) {
  switch (x) {
    default: zero();   break;
    case 1: one();     break;
    case 2: two();     break;
    case 3: three();  break;
    case 4: four();    break;
    case 5: five();     break;
    case 6: six();       break;
    case 7: seven(); break;
    case 8: eight();  break;
    case 9: nine();   break;
  }
}

// очистка индикатора
void clearLEDs() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void zero() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void one() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void two() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void three() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void four() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void five() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void six() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void seven() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void eight() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void nine() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void add() {
  count ++;
  if (count == 10) {
    count = 0;  n++;
    if (n == 10000) { n = 0; }
  }
}
