#define led_g 2
#define led_y 3
#define led_r 4
#define but1 5
#define but2 6
#define right1 7
#define left1 8
#define back 9
#define takeoff 10
#define landing 11
#define up 12
#define down 27
#define ok 14
#define toggle_lu 15
#define toggle_ld 16
#define toggle_l 17
#define toggle_ru 18
#define toggle_rd 19
#define toggle_r 20
#define sw1 21
#define sw2 22
#define dc 24
#define rst 25
#define cs 26
#define x1 A7
#define y1 A0
#define x2 A3
#define y2 A2
#define tw_l A4
#define tw_r A5
#define bat A6

#define err_x1_min -255
#define err_x1_max 255
#define err_y1_min -255
#define err_y1_max 255
#define err_x2_min -255
#define err_x2_max 255
#define err_y2_min -255
#define err_y2_max 255

#include <TFT.h>          // библиотека дисплея
#include <SPI.h>          // библиотека для работы с шиной SPI
#include <RF24.h>         // библиотека радиомодуля
#include <nRF24L01.h>     // библиотека радиомодуля
#include <GyverJoy.h>     // библиотека для работы с джойстиками

GyverJoy jx1;
GyverJoy jy1;
GyverJoy jx2;
GyverJoy jy2;
RF24 radio(23, 53);
TFT TFTscreen = TFT(cs, dc, rst);

byte flag1;
byte flag2;
byte flag3;
byte flag4;
byte flag5;
byte flag6;
byte flag7;
byte flag8;
byte flag9;
byte flag10;
byte flag11;
byte flag12;
byte flag13;
byte flag14;
byte flag15;
byte flag16;
byte flag17;
byte flag18;
byte flag19;
byte flag20;
byte flag21;
byte flag22;
int tw1;
int tw1_old;
int tw2;
int tw2_old;
int x11;
int y11;
int x22;
int y22;
int x11_old;
int y11_old;
int x22_old;
int y22_old;

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

const uint8_t num_channels = 128;
uint8_t values[num_channels];
const int num_reps = 100;
byte transmit_data[3];  // массив, хранящий передаваемые данные

void setup() {
  Serial.begin(9600);

  printf_begin();

  jx1.calibrate(analogRead(x1));
  jy1.calibrate(analogRead(y1));
  jx2.calibrate(analogRead(x2));
  jy2.calibrate(analogRead(y2));
  jx1.deadzone(0);
  jy1.deadzone(0);
  jx2.deadzone(0);
  jy2.deadzone(0);
  jx1.exponent(GJ_LINEAR);
  jy1.exponent(GJ_LINEAR);
  jx2.exponent(GJ_LINEAR);
  jy2.exponent(GJ_LINEAR);
  jy1.invert(true);
  jy2.invert(true);

  pinMode(led_g, OUTPUT);
  pinMode(led_y, OUTPUT);
  pinMode(led_r, OUTPUT);
  pinMode(but1, INPUT_PULLUP);
  pinMode(but2, INPUT_PULLUP);
  pinMode(right1, INPUT_PULLUP);
  pinMode(left1, INPUT_PULLUP);
  pinMode(back, INPUT_PULLUP);
  pinMode(takeoff, INPUT_PULLUP);
  pinMode(landing, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(ok, INPUT_PULLUP);
  pinMode(toggle_lu, INPUT_PULLUP);
  pinMode(toggle_ld, INPUT_PULLUP);
  pinMode(toggle_l, INPUT_PULLUP);
  pinMode(toggle_ru, INPUT_PULLUP);
  pinMode(toggle_rd, INPUT_PULLUP);
  pinMode(toggle_r, INPUT_PULLUP);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);

  pinMode(53, OUTPUT);
  pinMode(cs, OUTPUT);

  digitalWrite(cs, HIGH);
  digitalWrite(53, HIGH);
  delay(10);
  digitalWrite(53, LOW);

  radio.begin();              // активировать модуль
  radio.setAutoAck(1);        // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();   // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);   // размер пакета, в байтах

  radio.openWritingPipe(address[0]);  // мы - труба 0, открываем канал для передачи данных
  radio.setChannel(0x60);             // выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX);   // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp();        // начать работу
  radio.stopListening();  // не слушаем радиоэфир, мы передатчик

  digitalWrite(53, HIGH);
  digitalWrite(cs, LOW);

  TFTscreen.begin();
  TFTscreen.background(255, 255, 255);
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.fill(255, 255, 255);
  TFTscreen.circle(20, 113, 10);
  TFTscreen.circle(20, 88, 10);
  TFTscreen.circle(20, 63, 10);
  TFTscreen.circle(15, 38, 10);
  TFTscreen.circle(15, 13, 10);

  TFTscreen.circle(140, 113, 10);
  TFTscreen.circle(140, 88, 10);
  TFTscreen.circle(140, 63, 10);
  TFTscreen.circle(145, 38, 10);
  TFTscreen.circle(145, 13, 10);

  tw1_old = tw1;
  tw1 = 39 - map(analogReadStab(tw_l), 0, 1023, 0, 39);
  TFTscreen.noFill();
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.circle(35 + tw1_old, 113, 3);
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.line(35, 113, 74, 113);
  TFTscreen.circle(35 + tw1, 113, 3);

  tw2_old = tw2;
  tw2 = 39 - map(analogReadStab(tw_r), 0, 1023, 0, 39);
  TFTscreen.noFill();
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.circle(84 + tw2_old, 113, 3);
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.line(84, 113, 123, 113);
  TFTscreen.circle(84 + tw2, 113, 3);
}

void loop() {
  digitalWrite(led_g, HIGH);
  /*digitalWrite(led_y, HIGH);
    digitalWrite(led_r, HIGH);*/
  digitalWrite(cs, HIGH);
  digitalWrite(53, LOW);

  transmit_data[0] = abs(jy1.compute(analogRead(y1)));  // массив, хранящий передаваемые данные
  Serial.println(transmit_data[0]);
  radio.powerUp();    // включить передатчик
  radio.write(&transmit_data, sizeof(transmit_data)); // отправить по радио
  radio.powerDown();  // выключить передатчик

  digitalWrite(cs, LOW);
  digitalWrite(53, HIGH);
  delay(10);
  if (digitalRead(back) == 0 && flag1 == 0) {//1
    TFTscreen.fill(0, 0, 0);
    TFTscreen.circle(20, 113, 10);
    flag1 = 1;
  }
  if (digitalRead(back) == 1 && flag1 == 1) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.circle(20, 113, 10);
    flag1 = 0;
  }

  if (digitalRead(left1) == 0 && flag2 == 0) {//2
    TFTscreen.fill(0, 0, 0);
    TFTscreen.circle(20, 88, 10);
    flag2 = 1;
  }
  if (digitalRead(left1) == 1 && flag2 == 1) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.circle(20, 88, 10);
    flag2 = 0;
  }

  if (digitalRead(right1) == 0 && flag3 == 0) {//3
    TFTscreen.fill(0, 0, 0);
    TFTscreen.circle(20, 63, 10);
    flag3 = 1;
  }
  if (digitalRead(right1) == 1 && flag3 == 1) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.circle(20, 63, 10);
    flag3 = 0;
  }

  if (digitalRead(but2) == 0 && flag4 == 0) {//4
    TFTscreen.fill(0, 0, 0);
    TFTscreen.circle(15, 38, 10);
    flag4 = 1;
  }
  if (digitalRead(but2) == 1 && flag4 == 1) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.circle(15, 38, 10);
    flag4 = 0;
  }

  if (digitalRead(but1) == 0 && flag5 == 0) {//5
    TFTscreen.fill(0, 0, 0);
    TFTscreen.circle(15, 13, 10);
    flag5 = 1;
  }
  if (digitalRead(but1) == 1 && flag5 == 1) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.circle(15, 13, 10);
    flag5 = 0;
  }

  if (digitalRead(ok) == 0 && flag6 == 0) {//6
    TFTscreen.fill(0, 0, 0);
    TFTscreen.circle(140, 113, 10);
    flag6 = 1;
  }
  if (digitalRead(ok) == 1 && flag6 == 1) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.circle(140, 113, 10);
    flag6 = 0;
  }

  if (digitalRead(down) == 0 && flag7 == 0) {//7
    TFTscreen.fill(0, 0, 0);
    TFTscreen.circle(140, 88, 10);
    flag7 = 1;
  }
  if (digitalRead(down) == 1 && flag7 == 1) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.circle(140, 88, 10);
    flag7 = 0;
  }

  if (digitalRead(up) == 0 && flag8 == 0) {//8
    TFTscreen.fill(0, 0, 0);
    TFTscreen.circle(140, 63, 10);
    flag8 = 1;
  }
  if (digitalRead(up) == 1 && flag8 == 1) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.circle(140, 63, 10);
    flag8 = 0;
  }

  if (digitalRead(landing) == 0 && flag9 == 0) {//9
    TFTscreen.fill(0, 0, 0);
    TFTscreen.circle(145, 38, 10);
    flag9 = 1;
  }
  if (digitalRead(landing) == 1 && flag9 == 1) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.circle(145, 38, 10);
    flag9 = 0;
  }

  if (digitalRead(takeoff) == 0 && flag10 == 0) {//10
    TFTscreen.fill(0, 0, 0);
    TFTscreen.circle(145, 13, 10);
    flag10 = 1;
  }
  if (digitalRead(takeoff) == 1 && flag10 == 1) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.circle(145, 13, 10);
    flag10 = 0;
  }

  tw1_old = tw1;
  tw1 = 39 - map(analogReadStab(tw_l), 0, 1023, 0, 39);
  //tw1 = analogReadStab(tw1);
  if (tw1 != tw1_old) {
    TFTscreen.noFill();
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.circle(35 + tw1_old, 113, 3);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.line(35, 113, 74, 113);
    TFTscreen.circle(35 + tw1, 113, 3);
  }

  tw2_old = tw2;
  tw2 = 39 - map(analogReadStab(tw_r), 0, 1023, 0, 39);
  if (tw2 != tw2_old) {
    TFTscreen.noFill();
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.circle(84 + tw2_old, 113, 3);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.line(84, 113, 123, 113);
    TFTscreen.circle(84 + tw2, 113, 3);
  }

  //TFTscreen.line(35, 63, 74, 63);
  //TFTscreen.line(84, 63, 123, 63);
  flag12 = flag11;
  if (digitalRead(sw1) == 0 && flag11 == 0) {//10
    flag11 = 1;
  }
  if (digitalRead(sw1) == 1 && flag11 == 1) {
    flag11 = 0;
  }

  x11_old = x11;
  y11_old = y11;
  x11 = map(jx1.compute(analogRead(x1)), err_x1_min, err_x1_max, 0, 39);
  y11 = map(jy1.compute(analogRead(y1)), err_y1_min, err_y1_max, 0, 39);
  if (x11 != x11_old || y11 != y11_old || flag11 != flag12) {
    TFTscreen.stroke(255, 255, 255);
    if (flag11 == 0) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.circle(35 + x11_old, 44 + y11_old, 3);
      TFTscreen.noFill();
    }
    if (flag11 == 1) {
      TFTscreen.fill(255, 255, 255);
    }
    TFTscreen.circle(35 + x11_old, 44 + y11_old, 3);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.line(35, 63, 74, 63);
    TFTscreen.line(54, 44, 54, 82);
    if (flag11 == 1) {
      TFTscreen.fill(0, 0, 0);
    }
    TFTscreen.circle(35 + x11, 44 + y11, 3);
  }

  flag14 = flag13;
  if (digitalRead(sw2) == 0 && flag13 == 0) {//10
    flag13 = 1;
  }
  if (digitalRead(sw2) == 1 && flag13 == 1) {
    flag13 = 0;
  }

  x22_old = x22;
  y22_old = y22;
  x22 = map(jx2.compute(analogRead(x2)), err_x2_min, err_x2_max, 0, 39);
  y22 = map(jy2.compute(analogRead(y2)), err_y2_min, err_y2_max, 0, 39);
  if (x22 != x22_old || y22 != y22_old || flag13 != flag14) {
    TFTscreen.stroke(255, 255, 255);
    if (flag13 == 0) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.circle(84 + x22_old, 44 + y22_old, 3);
      TFTscreen.noFill();
    }
    if (flag13 == 1) {
      TFTscreen.fill(255, 255, 255);
    }
    TFTscreen.circle(84 + x22_old, 44 + y22_old, 3);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.line(84, 63, 123, 63);
    TFTscreen.line(103, 44, 103, 82);
    if (flag13 == 1) {
      TFTscreen.fill(0, 0, 0);
    }
    TFTscreen.circle(84 + x22, 44 + y22, 3);
  }

  flag15 = flag16;
  if (digitalRead(toggle_lu) == 0) {
    flag16 = 2;
  }
  else if (digitalRead(toggle_ld) == 0) {
    flag16 = 0;
  }
  else {
    flag16 = 1;
  }
  if (flag15 != flag16) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.circle(44, 10 + flag15 * 10, 3);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.line(44, 10, 44, 30);
    TFTscreen.line(43, 10, 46, 10);
    TFTscreen.line(43, 20, 46, 20);
    TFTscreen.line(43, 30, 46, 30);
    TFTscreen.circle(44, 10 + flag16 * 10, 3);
  }

  flag17 = flag18;
  flag18 = digitalRead(toggle_l);
  if (flag17 != flag18) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.circle(64, 10 + flag17 * 20, 3);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.line(64, 10, 64, 30);
    TFTscreen.line(63, 10, 66, 10);
    TFTscreen.line(63, 30, 66, 30);
    TFTscreen.circle(64, 10 + flag18 * 20, 3);
  }

  flag19 = flag20;
  flag20 = digitalRead(toggle_r);
  if (flag19 != flag20) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.circle(93, 10 + flag19 * 20, 3);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.line(93, 10, 93, 30);
    TFTscreen.line(92, 10, 95, 10);
    TFTscreen.line(92, 30, 95, 30);
    TFTscreen.circle(93, 10 + flag20 * 20, 3);
  }

  flag21 = flag22;
  if (digitalRead(toggle_ru) == 0) {
    flag22 = 2;
  }
  else if (digitalRead(toggle_rd) == 0) {
    flag22 = 0;
  }
  else {
    flag22 = 1;
  }
  if (flag21 != flag22) {
    TFTscreen.fill(255, 255, 255);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.circle(113, 10 + flag21 * 10, 3);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.line(113, 10, 113, 30);
    TFTscreen.line(112, 10, 115, 10);
    TFTscreen.line(112, 20, 115, 20);
    TFTscreen.line(112, 30, 115, 30);
    TFTscreen.circle(113, 10 + flag22 * 10, 3);
  }
}

int analogReadStab(byte analogPin) {
  long sum = 0;
  for (int p = 0; p <= 255; p++) {
    sum += analogRead(analogPin);
  }
  sum = sum >> 8;
  return sum;
}

int serial_putc( char c, FILE * ) {
  Serial.write( c );
  return c;
}

void printf_begin(void) {
  fdevopen( &serial_putc, 0 );
}
