#define D1 2
#define D2 3
#define D3 4
#define D4 5
#define A 6
#define B 7
#define C 8
#define D 9
#define E 10
#define F 11
#define G 12
#define DP 13
#define kn1 A0//кнопка выбора объекта //кнопка изменения времени
#define kn2 A1//кнопка выбора значения //кнопка запуска будильника
#define zum A2//пищалка

#include <GyverButton.h>
GButton butt1(kn1);//кнопка выбора объекта //кнопка изменения времени
GButton butt2(kn2);//кнопка выбора значения //кнопка запуска будильника

unsigned long timing;//моргание точек(для millis)
unsigned long timing2;//моргание точек(для millis)
int x = 500;//моргание точек(для millis)
int h1;//часы левый символ(1)
int h2;//часы второй символ(2)
int m1;//минуты первый символ(3)
int m2;//минуты второй символ(4)
int y = 4;//задержка после case
int y1 = 100;//задержка для заставки
bool z;
int x1;
int x2;
 
void setup() {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);
  pinMode(zum, OUTPUT);//пищалка
  Serial.begin(9600);
}

void loop() {
  if(x1==0){
    zastavka();
    x1 = 1;
  }
  if(x1==1){
    timer();
  }
  
}

void zastavka() {
  digitalWrite(D1, LOW);//заставка №1
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  delay(y1);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  delay(y1);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  delay(y1);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  delay(y1);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  delay(y1);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  delay(y1);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  delay(y1);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  delay(y1);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  delay(y1);

  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  delay(y1);

  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  delay(y1);

  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
  delay(y1);//заставка №1

  digitalWrite(D1, LOW);//заставка №2
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(DP, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(DP, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(DP, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(DP, LOW);
  delay(1000);
  digitalWrite(D1, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(DP, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(DP, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(DP, LOW);
  digitalWrite(D4, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(DP, LOW);
  delay(500);//заставка №2
}

void timer() {
  if(x2==0){
    h1 = 10;
    x2 = 1;
  }
  if(x2==1){
    h1 = 2;
  }


 /* butt1.tick();
  butt2.tick();
  if (butt1.isClick()){
    z = !z;
    Serial.println(z);
  }*/

  
  switch (h1) {
    case 0:
      digitalWrite(D1, LOW);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 1:
      digitalWrite(D1, LOW);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 2:
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 3:
      digitalWrite(D1, LOW);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 4:
      digitalWrite(D1, LOW);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 5:
      digitalWrite(D1, LOW);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 6:
      digitalWrite(D1, LOW);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 7:
      digitalWrite(D1, LOW);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 8:
      digitalWrite(D1, LOW);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 9:
      digitalWrite(D1, LOW);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 10:
      digitalWrite(D1, HIGH);
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
  }


  switch (h2) {
    case 0:
      //digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 1:
      //digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 2:
      //digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 3:
      //digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 4:
      //digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 5:
      //digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 6:
      //digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 7:
      //digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 8:
      //digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 9:
      //digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      //digitalWrite(D3, HIGH);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 10:
      digitalWrite(D2, HIGH);
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
  }


  switch (m1) {
    case 0:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 1:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 2:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 3:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 4:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 5:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 6:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 7:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 8:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 9:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //digitalWrite(D4, HIGH);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 10:
      digitalWrite(D3, HIGH);
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
  }


  switch (m2) {
    case 0:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 1:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 2:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 3:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 4:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 5:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 6:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 7:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 8:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 9:
      //digitalWrite(D1, HIGH);
      //digitalWrite(D2, HIGH);
      //digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(DP, LOW);
      delay(y);
      break;
    case 10:
      digitalWrite(D4, HIGH);
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      digitalWrite(DP, LOW);
      delay(y);
      break;
  }
}
/*if (millis() - timing > 1000) { // Вместо 10000 подставьте нужное вам значение паузы
  timing = millis();
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);

  }
  if (millis() - timing2 > x) { // Вместо 10000 подставьте нужное вам значение паузы
  timing2 = millis();
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  x = 1000;
  }*/
