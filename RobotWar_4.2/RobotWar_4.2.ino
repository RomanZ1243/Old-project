#define MRF 18
#define BRF 4
#define MLF 12
#define BLF 32
#define MRB 19
#define BRB 13
#define MLB 27
#define BLB 34
#define GUN 36

#define err 10
#define braking 255

#include <IBusBM.h>
#include <GyverWDT.h>

IBusBM IBus;    // IBus object

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
boolean brake_rf;
boolean brake_lf;
boolean brake_rb;
boolean brake_lb;
boolean gun;

void setup() {
  IBus.begin(Serial);    // iBUS object connected to serial0 RX pin
  pinMode(MRF, OUTPUT);
  pinMode(BRF, OUTPUT);
  pinMode(MLF, OUTPUT);
  pinMode(BLF, OUTPUT);
  pinMode(MRB, OUTPUT);
  pinMode(BRB, OUTPUT);
  pinMode(MLB, OUTPUT);
  pinMode(BLB, OUTPUT);
  pinMode(GUN, OUTPUT);
  Watchdog.enable(RESET_MODE, WDT_PRESCALER_64);
}

void loop() {
  IBus.loop();
  stX = IBus.readChannel(0);//повороты
  stY = IBus.readChannel(1);//вперед/назад
  swA = IBus.readChannel(4);//оружие
  swB = IBus.readChannel(5);//торможение
  //swC = IBus.readChannel(6);//режимы моторов подный привод
  swD = IBus.readChannel(7);//вкл/откл питания
  vrA = IBus.readChannel(8);//максимальная скорость поворотов
  vrB = IBus.readChannel(9);//максимальная скорость передвижения вперед/назад
  vrA = map(vrA, 1000, 2000, 0, 255);
  vrB = map(vrB, 1000, 2000, 0, 255);

  if (swD >= 2000 - err && swD <= 2000 + err) {
    if ((stX >= 1500 - err && stX <= 1500 + err) && (stY >= 1500 + err || stY <= 1500 - err)) { //движение вперед/назад
      if (stY < 1500) {
        speed_rf = 0;
        speed_lf = 0;
        speed_rb = map(stY, 1000, 1500, vrB, 0);
        speed_lb = map(stY, 1000, 1500, vrB, 0);
      }
      if (stY > 1500) {
        speed_rf = map(stY, 1500, 2000, 0, vrB);
        speed_lf = map(stY, 1500, 2000, 0, vrB);
        speed_rb = 0;
        speed_lb = 0;
      }
    }
    else if ((stY >= 1500 - err && stY <= 1500 + err) && (stX >= 1500 + err || stX <= 1500 - err)) {//поворот танком
      if (stX < 1500) {
        speed_rf = map(stX, 1000, 1500, vrA, 0);
        speed_lf = 0;
        speed_rb = 0;
        speed_lb = map(stX, 1000, 1500, vrA, 0);
      }
      if (stX > 1500) {
        speed_rf = 0;
        speed_lf = map(stX, 1500, 2000, 0, vrA);
        speed_rb = map(stX, 1500, 2000, 0, vrA);
        speed_lb = 0;
      }
    }
    else if (swB >= 2000 - err && swB <= 2000 + err) {//тормоз (если включон)
      speed_rf = 0;
      speed_lf = 0;
      speed_rb = 0;
      speed_lb = 0;
      brake_rf = 1;
      brake_lf = 1;
      brake_rb = 1;
      brake_lb = 1;
    }
    else if (swB >= 1000 - err && swB <= 1000 + err) {//обычный режим
      speed_rf = 0;
      speed_lf = 0;
      speed_rb = 0;
      speed_lb = 0;
      brake_rf = 0;
      brake_lf = 0;
      brake_rb = 0;
      brake_lb = 0;
    }
    if (swA >= 2000 - err && swA <= 2000 + err) {
      gun = 1;
    }
    else {
      gun = 0;
    }
  }
  else {
    speed_rf = 0;
    speed_lf = 0;
    speed_rb = 0;
    speed_lb = 0;
    brake_rf = 0;
    brake_lf = 0;
    brake_rb = 0;
    brake_lb = 0;
    gun = 0;
  }
  analogWrite(MRF, speed_rf);
  analogWrite(MLF, speed_lf);
  analogWrite(MRB, speed_rb);
  analogWrite(MLB, speed_lb);
  analogWrite(BRF, brake_rf);
  analogWrite(BLF, brake_lf);
  analogWrite(BRB, brake_rb);
  analogWrite(BLB, brake_lb);
  digitalWrite(GUN, gun);

  Serial.print(speed_lf);
  Serial.print(" ");
  Serial.print(speed_rf);
  Serial.println(" ");
  Serial.print(speed_lb);
  Serial.print(" ");
  Serial.println(speed_rb);
  Serial.print("============================================ ");
  Serial.println(gun);

  Watchdog.reset();
}
