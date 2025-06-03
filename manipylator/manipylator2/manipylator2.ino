#define SW 3    //кнопка
#define CLK 5   //энкодер
#define DT 6    //энкодер
#define S1 7    //поворот
#define S2 8    //нижний подъем
#define S3 9    //верхний подъем
#define S4 10    //захват
#define B 11     //светодиод красный цвет
#define G 12     //светодиод зеленый цвет
#define R 13    //светодиод синий цвет

#include <Servo.h>         //библиотека для сервоприводов
#include <GyverEncoder.h>  //библиотека для энкодера
#include <GyverButton.h>   //библиотека для кнопки

Encoder enc1(CLK, DT);   //подключаем энкодер
GButton butt1(SW);       //подключаем кнопку
Servo myservo1;          //подключаем сервопривод (поворот)
Servo myservo2;          //подключаем сервопривод (нижний подъем)
Servo myservo3;          //подключаем сервопривод (верхний подъем)
Servo myservo4;          //подключаем сервопривод (захват)

int x;          //смена режимов
int x1 = 0;         //сервопривод (поворот)
int x2 = 10;         //сервопривод (нижний подъем)
int x3 = 110;         //сервопривод (верхний подъем)
int x4 = 70;         //сервопривод (захват)
int y = 5;      //быстрый поворот энкодера

void setup() {
  Serial.begin(9600);
  butt1.setTickMode(AUTO);
  enc1.setTickMode(AUTO);
  enc1.setType(TYPE2);     // тип энкодера TYPE1 одношаговый
  myservo1.attach(S1);     //подключаем сервопривод (поворот)
  myservo2.attach(S2);     //подключаем сервопривод (нижний подъем)
  myservo3.attach(S3);     //подключаем сервопривод (верхний подъем)
  myservo4.attach(S4);     //подключаем сервопривод (захват)
  pinMode(R, OUTPUT);      //подключаем светодиод красный цвет
  pinMode(G, OUTPUT);      //подключаем светодиод зеленый цвет
  pinMode(B, OUTPUT);      //подключаем светодиод синий цвет
}

void loop() {
  //смена режимов
  if (butt1.isPress()) {
    x++;
    if (x == 4) {
      x = 0;
    }
  }

  //поворот
  if (x == 0) {
    Serial.print(x);
    Serial.print(" - ");
    Serial.println(x1);
    myservo1.write(x1);
    myservo2.write(x2);
    myservo3.write(x3);
    myservo4.write(x4);
    digitalWrite(R, HIGH);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
    if (enc1.isRight()) {
      x1++;
    }
    if (enc1.isLeft()) {
      x1--;
    }
    if (x1 < 0) {
      x1 = 0;
    }
    if (x1 > 160) {
      x1 = 160;
    }
  }

  //нижний подъем
  if (x == 1) {
    Serial.print(x);
    Serial.print(" - ");
    Serial.println(x2);
    myservo1.write(x1);
    myservo2.write(x2);
    myservo3.write(x3);
    myservo4.write(x4);
    digitalWrite(R, LOW);
    digitalWrite(G, HIGH);
    digitalWrite(B, LOW);
    if (enc1.isRight()) {
      x2++;
    }
    if (enc1.isLeft()) {
      x2--;
    }
    if (x2 < 10) {
      x2 = 10;
    }
    if (x2 > 110) {
      x2 = 110;
    }
    if(x2 < 0){
      x2 = 0;
    }
  }

  //верхний подъем
  if (x == 2) {
    Serial.print(x);
    Serial.print(" - ");
    Serial.println(x3);
    myservo1.write(x1);
    myservo2.write(x2);
    myservo3.write(x3);
    myservo4.write(x4);
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, HIGH);
    if (enc1.isRight()) {
      x3++;
    }
    if (enc1.isLeft()) {
      x3--;
    }
    if (x3 < 110) {
      x3 = 110;
    }
    if (x3 > 180) {
      x3 = 180;
    }
    if(x3 < 0){
      x3 = 0;
    }
  }

  //захват
  if (x == 3) {
    Serial.print(x);
    Serial.print(" - ");
    Serial.println(x4);
    myservo1.write(x1);
    myservo2.write(x2);
    myservo3.write(x3);
    myservo4.write(x4);
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
    if (enc1.isRight()) {
      x4++;
    }
    if (enc1.isLeft()) {
      x4--;
    }
    if (x4 < 70) {
      x4 = 70;
    }
    if (x4 > 150) {
      x4 = 150;
    }
    if(x4 < 0){
      x4 = 0;
    }
  }
}
