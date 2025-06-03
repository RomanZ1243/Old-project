#define MLF 9 //12
#define MRB 5 //18
#define MLB 10  //27
#define MRF 6 //19

#define BLF 4 //32
#define BRB A4 //4
#define BLB 3  //34
#define BRF A5 //13

#define RLF 11 //32
#define RRF A0 //4
#define RLB 8  //34
#define RRB A3 //13

#define GUN 7  //36
#define PIN 12 //14

#define err 100      //настройка мертвой зоны
#define reset1 2000 //настройка интервала перезагрузки приемника
#define reset2 10000 //настройка интервала перезагрузки приемника

#include <IBusBM.h>
//#include "IBusBM_2.h"
#include <GyverWDT.h>

IBusBM IBus;

int stX;
int stY;
int swA;
int swB;
int swC;
int swD;
int vrA;
int vrB;
int speed_rf;
int speed_lf;
int speed_rb;
int speed_lb;
boolean brake;
boolean brake_rf;
boolean brake_lf;
boolean brake_rb;
boolean brake_lb;
boolean revers_rf;
boolean revers_lf;
boolean revers_rb;
boolean revers_lb;
boolean gun;

void setup() {
  IBus.begin(Serial);

  pinMode(MLF, OUTPUT);
  pinMode(MRF, OUTPUT);
  pinMode(MLB, OUTPUT);
  pinMode(MRB, OUTPUT);

  pinMode(RLF, OUTPUT);
  pinMode(RRF, OUTPUT);
  pinMode(RLB, OUTPUT);
  pinMode(RRB, OUTPUT);

  pinMode(BLF, OUTPUT);
  pinMode(BRF, OUTPUT);
  pinMode(BLB, OUTPUT);
  pinMode(BRB, OUTPUT);

  pinMode(GUN, OUTPUT);
  pinMode(PIN, INPUT);

  Watchdog.enable(RESET_MODE, WDT_PRESCALER_64);
}

void loop() {
  //IBus.loop();    

  speed_rf = 0;
  speed_lf = 0;
  speed_rb = 0;
  speed_lb = 0;
  brake_rf = 0;
  brake_lf = 0;
  brake_rb = 0;
  brake_lb = 0;

  stX = IBus.readChannel(0);  //повороты
  stY = IBus.readChannel(1);  //вперед/назад
  swA = IBus.readChannel(4);  //оружие
  swB = IBus.readChannel(5);  //торможение
  swC = IBus.readChannel(6);  //выкл. тормозов/тормоза только на поворотах/тормоза на поворотах и на парковке
  swD = IBus.readChannel(7);  //вкл/откл питания (предохранитель)
  vrA = IBus.readChannel(8);  //максимальная скорость передвижения
  //vrB = IBus.readChannel(9);  //максимальная скорость передвижения
  vrA = map(vrA, 1000, 2000, 0, 255);
  swC = swC / 500 - 2;
  if (swC == 2) {
    swC = 1;
    brake = 1;
  }
  else {
    brake = 0;
  }
  //vrB = map(vrB, 1000, 2000, 0, 255);

  if (swD >= 2000 - err && swD <= 2000 + err) {
    if ((stX >= 1500 - err && stX <= 1500 + err) && (stY >= 1500 + err || stY <= 1500 - err)) { //движение вперед/назад
      if (stY < 1500) {
        speed_rf = 0;
        speed_lf = 0;
        speed_rb = map(stY, 1000, 1500, vrA, 0);
        speed_lb = map(stY, 1000, 1500, vrA, 0);
        revers_rf = 1;
        revers_lf = 1;
        revers_rb = 0;
        revers_lb = 0;
      }
      if (stY > 1500) {
        speed_rf = map(stY, 1500, 2000, 0, vrA);
        speed_lf = map(stY, 1500, 2000, 0, vrA);
        speed_rb = 0;
        speed_lb = 0;
        revers_rf = 0;
        revers_lf = 0;
        revers_rb = 1;
        revers_lb = 1;
      }
      brake_rf = 0;
      brake_lf = 0;
      brake_rb = 0;
      brake_lb = 0;
    }
    else if ((stY >= 1500 - err && stY <= 1500 + err) && (stX >= 1500 + err || stX <= 1500 - err)) {  //поворот танком
      if (stX < 1500) { //налево
        speed_rf = map(stX, 1000, 1500, vrA, 0);
        speed_lf = 0;
        speed_rb = 0;
        speed_lb = map(stX, 1000, 1500, vrA, 0);
        brake_rf = 0;
        brake_lf = swC;
        brake_rb = swC;
        brake_lb = 0;
      }
      if (stX > 1500) { //направо
        speed_rf = 0;
        speed_lf = map(stX, 1500, 2000, 0, vrA);
        speed_rb = map(stX, 1500, 2000, 0, vrA);
        speed_lb = 0;
        brake_rf = swC;
        brake_lf = 0;
        brake_rb = 0;
        brake_lb = swC;
      }
      revers_rf = 0;
      revers_lf = 0;
      revers_rb = 0;
      revers_lb = 0;
    }
    else if ((stY < 1500 - err || stY > 1500 + err) && (stX > 1500 + err || stX < 1500 - err)) { //повороты циркулем
      if (stX < 1500 && stY > 1500) { //если джостик слева сверху
        speed_rf = map(stY, 1500, 2000, 0, vrA);
        speed_lf = map(stX, 1000, 1500, 0, speed_rf);
        speed_rb = 0;
        speed_lb = 0;
        brake_rf = 0;
        brake_lf = 0;
        brake_rb = 0;
        brake_lb = swC;
      }
      if (stX > 1500 && stY > 1500) { //если джостик справа сверху
        speed_lf = map(stY, 1500, 2000, 0, vrA);
        speed_rf = map(2000 - stX, 0, 500, 0, speed_lf);
        speed_rb = 0;
        speed_lb = 0;
        brake_rf = 0;
        brake_lf = 0;
        brake_rb = swC;
        brake_lb = 0;
      }
      if (stX > 1500 && stY < 1500) { //если джостик справа снизу
        speed_lf = 0;
        speed_rf = 0;
        speed_lb = map(stY, 1000, 1500, vrA, 0);
        speed_rb = map(2000 - stX, 0, 500, 0, speed_lb);
        brake_rf = swC;
        brake_lf = 0;
        brake_rb = 0;
        brake_lb = 0;
      }
      if (stX < 1500 && stY < 1500) { //если джостик слева снизу
        speed_lf = 0;
        speed_rf = 0;
        speed_rb = map(stY, 1000, 1500, vrA, 0);
        speed_lb = map(stX, 1000, 1500, 0, speed_rb);
        brake_rf = 0;
        brake_lf = swC;
        brake_rb = 0;
        brake_lb = 0;
      }
      revers_rf = 0;
      revers_lf = 0;
      revers_rb = 0;
      revers_lb = 0;
    }
    else if ((stX >= 1500 - err && stX <= 1500 + err) && (stY <= 1500 + err && stY >= 1500 - err)) { //обнуление пинов (тормоз включается если swC == 2000)
      speed_rf = 0;
      speed_lf = 0;
      speed_rb = 0;
      speed_lb = 0;
      /*brake_rf = swB;
        brake_lf = swB;
        brake_rb = swB;
        brake_lb = swB;*/
      brake_rf = brake;
      brake_lf = brake;
      brake_rb = brake;
      brake_lb = brake;
      revers_rf = 0;
      revers_lf = 0;
      revers_rb = 0;
      revers_lb = 0;
    }
    if (swA >= 2000 - err && swA <= 2000 + err) { //управление оружием
      gun = 1;
    }
    else {
      gun = 0;
    }
  }
  else {  //обнуление, если переключатель swD выключен
    speed_rf = 0;
    speed_lf = 0;
    speed_rb = 0;
    speed_lb = 0;
    brake_rf = 0;
    brake_lf = 0;
    brake_rb = 0;
    brake_lb = 0;
    revers_rf = 0;
    revers_lf = 0;
    revers_rb = 0;
    revers_lb = 0;
    gun = 0;
  }

  //отправка данных
  analogWrite(MRF, speed_rf);
  analogWrite(MLF, speed_lf);
  analogWrite(MRB, speed_rb);
  analogWrite(MLB, speed_lb);

  digitalWrite(BRF, brake_rf);
  digitalWrite(BLF, brake_lf);
  digitalWrite(BRB, brake_rb);
  digitalWrite(BLB, brake_lb);

  /*digitalWrite(RRF, revers_rf);
    digitalWrite(RLF, revers_lf);
    digitalWrite(RRB, revers_rb);
    digitalWrite(RLB, revers_lb);*/
  digitalWrite(GUN, gun);

  /*Serial.print(speed_lf);
    Serial.print(" ");
    Serial.print(speed_rf);
    Serial.println(" ");
    Serial.print(speed_lb);
    Serial.print(" ");
    Serial.println(speed_rb);
    Serial.print("============================================ ");
    Serial.println(gun);*/
  //delay(5);

  //перезагрузка при зависании
  Watchdog.reset();
}
