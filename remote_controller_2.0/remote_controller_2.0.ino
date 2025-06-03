#define LED_G 2
#define LED_Y 3
#define LED_R 4

#define BUT1 5
#define BUT2 6
#define BUT_RIGHT 7
#define BUT_LEFT 8
#define BUT_BACK 9
#define BUT_TAKEOFF 10
#define BUT_LANDING 11
#define BUT_UP 12
#define BUT_DOWN 27
#define BUT_OK 14

#define TOGGLE_LEFT_UP1 15
#define TOGGLE_LEFT_DOWN1 16
#define TOGGLE_LEFT 17
#define TOGGLE_RIGHT_UP1 18
#define TOGGLE_RIGHT_DOWN1 19
#define TOGGLE_RIGHT 20
#define TW_LEFT A4
#define TW_RIGHT A5

#define J_LEFT_X A7
#define J_LEFT_Y A0
#define J_RIGHT_X A3
#define J_RIGHT_Y A2
#define SW1 21
#define SW2 22

#define TFT_DC 24
#define TFT_RST 25
#define TFT_CS 26

#define NRF_CE 23
#define NRF_CSN 53

#define BAT A6

#define ERR_LEFT_X_MIN -255
#define ERR_LEFT_X_MAX 255
#define ERR_LEFT_Y_MIN -255
#define ERR_LEFT_Y_MAX 255
#define ERR_RIGHT_X_MIN -255
#define ERR_RIGHT_X_MAX 255
#define ERR_RIGHT_Y_MIN -255
#define ERR_RIGHT_Y_MAX 255

#include <TFT.h>          // библиотека дисплея
#include <SPI.h>          // библиотека для работы с шиной SPI
#include <RF24.h>         // библиотека радиомодуля
#include <nRF24L01.h>     // библиотека радиомодуля
#include <GyverJoy.h>     // библиотека для работы с джойстиками

GyverJoy JOY_LEFT_X;
GyverJoy JOY_LEFT_Y;
GyverJoy JOY_RIGHT_X;
GyverJoy JOY_RIGHT_Y;

RF24 radio(NRF_CE, NRF_CSN);
TFT TFTscreen = TFT(TFT_CS, TFT_DC, TFT_RST);

byte sensor_flag;

byte but_flag[22];
int sw_flag[6];   //TW_LEFT, TW_RIGHT, J_LEFT_X, J_LEFT_Y, J_RIGHT_X, J_RIGHT_Y
int sw_old_flag[6];

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

const uint8_t num_channels = 128;
uint8_t values[num_channels];
const int num_reps = 100;
int recieved_data[10];
byte transmit_data[3];  // массив, хранящий передаваемые данные

void setup() {
  Serial.begin(9600);

  printf_begin();

  JOY_LEFT_X.calibrate(analogRead(J_LEFT_X));
  JOY_LEFT_Y.calibrate(analogRead(J_LEFT_Y));
  JOY_RIGHT_X.calibrate(analogRead(J_RIGHT_X));
  JOY_RIGHT_Y.calibrate(analogRead(J_RIGHT_Y));
  JOY_LEFT_X.deadzone(5);
  JOY_LEFT_Y.deadzone(5);
  JOY_RIGHT_X.deadzone(5);
  JOY_RIGHT_Y.deadzone(5);
  JOY_LEFT_X.exponent(GJ_LINEAR);
  JOY_LEFT_Y.exponent(GJ_LINEAR);
  JOY_RIGHT_X.exponent(GJ_LINEAR);
  JOY_RIGHT_Y.exponent(GJ_LINEAR);
  JOY_LEFT_Y.invert(true);
  JOY_RIGHT_Y.invert(true);

  pinMode(LED_G, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUT1, INPUT_PULLUP);
  pinMode(BUT2, INPUT_PULLUP);
  pinMode(BUT_RIGHT, INPUT_PULLUP);
  pinMode(BUT_LEFT, INPUT_PULLUP);
  pinMode(BUT_BACK, INPUT_PULLUP);
  pinMode(BUT_TAKEOFF, INPUT_PULLUP);
  pinMode(BUT_LANDING, INPUT_PULLUP);
  pinMode(BUT_UP, INPUT_PULLUP);
  pinMode(BUT_DOWN, INPUT_PULLUP);
  pinMode(BUT_OK, INPUT_PULLUP);
  pinMode(TOGGLE_LEFT_UP1, INPUT_PULLUP);
  pinMode(TOGGLE_LEFT_DOWN1, INPUT_PULLUP);
  pinMode(TOGGLE_LEFT, INPUT_PULLUP);
  pinMode(TOGGLE_RIGHT_UP1, INPUT_PULLUP);
  pinMode(TOGGLE_RIGHT_DOWN1, INPUT_PULLUP);
  pinMode(TOGGLE_RIGHT, INPUT_PULLUP);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);

  pinMode(NRF_CSN, OUTPUT);
  pinMode(TFT_CS, OUTPUT);

  digitalWrite(TFT_CS, HIGH);
  digitalWrite(NRF_CSN, HIGH);
  delay(10);
  digitalWrite(NRF_CSN, LOW);

  radio.begin();              // активировать модуль
  radio.setAutoAck(1);        // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();   // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);   // размер пакета, в байтах

  radio.openWritingPipe(address[0]);  // мы - труба 0, открываем канал для передачи данных
  radio.setChannel(0x60);             // выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX);   // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_1MBPS); // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp();        // начать работу
  radio.stopListening();  // не слушаем радиоэфир, мы передатчик

  digitalWrite(NRF_CSN, HIGH);
  digitalWrite(TFT_CS, LOW);

  TFTscreen.begin();
  TFTscreen.background(255, 255, 255);
  TFTscreen.stroke(0, 0, 0);
}

void loop() {
  digitalWrite(LED_G, HIGH);
  /*digitalWrite(led_y, HIGH);
    digitalWrite(led_r, HIGH);*/

  send_signal();
  delay(2);
  recieve_signal();
  read_sensor_controller();
  delay(2);
}

void recieve_signal() {
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(NRF_CSN, LOW);
  radio.openReadingPipe(1, address[1]);   // хотим слушать трубу 0
  byte pipeNo;
  //radio.powerUp();
  radio.startListening();
  while ( radio.available(&pipeNo)) { // есть входящие данные
    radio.read(&recieved_data, sizeof(recieved_data));
    //analogWrite(13, recieved_data[0]);
    Serial.print(recieved_data[0]);
    Serial.print(' ');
    Serial.print(recieved_data[2]);
    Serial.print(' ');
    Serial.print(recieved_data[4]);
    Serial.print(' ');
    Serial.print(recieved_data[6]);
    Serial.print(' ');
    Serial.print(recieved_data[8]);
    Serial.println();
  }
}

void send_signal() {

  digitalWrite(TFT_CS, HIGH);
  digitalWrite(NRF_CSN, LOW);
  radio.openWritingPipe(address[0]);  // мы - труба 0, открываем канал для передачи данных
  radio.stopListening();
  transmit_data[0] = abs(JOY_LEFT_Y.compute(analogRead(J_LEFT_Y)));  // массив, хранящий передаваемые данные
  //Serial.println(transmit_data[0]);
  //radio.powerUp();    // включить передатчик
  radio.write(&transmit_data, sizeof(transmit_data)); // отправить по радио
  //radio.powerDown();  // выключить передатчик
}

void read_sensor_controller() {
  digitalWrite(TFT_CS, LOW);
  digitalWrite(NRF_CSN, HIGH);
  if (sensor_flag == 0) {
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

    but_flag[14] = but_flag[15];
    if (digitalRead(TOGGLE_LEFT_UP1) == 0) {
      but_flag[15] = 2;
    }
    else if (digitalRead(TOGGLE_LEFT_DOWN1) == 0) {
      but_flag[15] = 0;
    }
    else {
      but_flag[15] = 1;
    }
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.line(44, 10, 44, 30);
    TFTscreen.line(43, 10, 46, 10);
    TFTscreen.line(43, 20, 46, 20);
    TFTscreen.line(43, 30, 46, 30);
    TFTscreen.circle(44, 10 + but_flag[15] * 10, 3);

    but_flag[16] = but_flag[17];
    but_flag[17] = digitalRead(TOGGLE_LEFT);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.line(64, 10, 64, 30);
    TFTscreen.line(63, 10, 66, 10);
    TFTscreen.line(63, 30, 66, 30);
    TFTscreen.circle(64, 10 + but_flag[17] * 20, 3);

    but_flag[18] = but_flag[19];
    but_flag[19] = digitalRead(TOGGLE_RIGHT);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.line(93, 10, 93, 30);
    TFTscreen.line(92, 10, 95, 10);
    TFTscreen.line(92, 30, 95, 30);
    TFTscreen.circle(93, 10 + but_flag[19] * 20, 3);

    but_flag[20] = but_flag[21];
    if (digitalRead(TOGGLE_RIGHT_UP1) == 0) {
      but_flag[21] = 2;
    }
    else if (digitalRead(TOGGLE_RIGHT_DOWN1) == 0) {
      but_flag[21] = 0;
    }
    else {
      but_flag[21] = 1;
    }
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.line(113, 10, 113, 30);
    TFTscreen.line(112, 10, 115, 10);
    TFTscreen.line(112, 20, 115, 20);
    TFTscreen.line(112, 30, 115, 30);
    TFTscreen.circle(113, 10 + but_flag[21] * 10, 3);

    sw_old_flag[0] = sw_flag[0];
    sw_flag[0] = 39 - map(analogReadStab(TW_LEFT), 0, 1023, 0, 39);
    TFTscreen.noFill();
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.line(35, 113, 74, 113);
    TFTscreen.circle(35 + sw_flag[0], 113, 3);

    sw_old_flag[1] = sw_flag[1];
    sw_flag[1] = 39 - map(analogReadStab(TW_RIGHT), 0, 1023, 0, 39);
    TFTscreen.noFill();
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.line(84, 113, 123, 113);
    TFTscreen.circle(84 + sw_flag[1], 113, 3);

    sw_old_flag[2] = sw_flag[2];
    sw_old_flag[3] = sw_flag[3];
    sw_flag[2] = map(JOY_LEFT_X.compute(analogRead(J_LEFT_X)), ERR_LEFT_X_MIN, ERR_LEFT_X_MAX, 0, 39);
    sw_flag[3] = map(JOY_LEFT_Y.compute(analogRead(J_LEFT_Y)), ERR_LEFT_Y_MIN, ERR_LEFT_Y_MAX, 0, 39);
    TFTscreen.fill(255, 255, 255);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.circle(35 + sw_flag[2], 44 + sw_flag[3], 3);
    TFTscreen.line(35, 63, 74, 63);
    TFTscreen.line(54, 44, 54, 82);

    sw_old_flag[4] = sw_flag[4];
    sw_old_flag[5] = sw_flag[5];
    sw_flag[4] = map(JOY_RIGHT_X.compute(analogRead(J_RIGHT_X)), ERR_RIGHT_X_MIN, ERR_RIGHT_X_MAX, 0, 39);
    sw_flag[5] = map(JOY_RIGHT_Y.compute(analogRead(J_RIGHT_Y)), ERR_RIGHT_Y_MIN, ERR_RIGHT_Y_MAX, 0, 39);
    TFTscreen.fill(255, 255, 255);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.circle(84 + sw_flag[4], 44 + sw_flag[5], 3);
    TFTscreen.line(84, 63, 123, 63);
    TFTscreen.line(103, 44, 103, 82);

    sensor_flag = 1;
  }

  if (sensor_flag == 1) {
    if (digitalRead(BUT_BACK) == 0 && but_flag[0] == 0) {//1
      TFTscreen.fill(0, 0, 0);
      TFTscreen.circle(20, 113, 10);
      but_flag[0] = 1;
    }
    if (digitalRead(BUT_BACK) == 1 && but_flag[0] == 1) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.circle(20, 113, 10);
      but_flag[0] = 0;
    }

    if (digitalRead(BUT_LEFT) == 0 && but_flag[1] == 0) {//2
      TFTscreen.fill(0, 0, 0);
      TFTscreen.circle(20, 88, 10);
      but_flag[1] = 1;
    }
    if (digitalRead(BUT_LEFT) == 1 && but_flag[1] == 1) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.circle(20, 88, 10);
      but_flag[1] = 0;
    }

    if (digitalRead(BUT_RIGHT) == 0 && but_flag[2] == 0) {//3
      TFTscreen.fill(0, 0, 0);
      TFTscreen.circle(20, 63, 10);
      but_flag[2] = 1;
    }
    if (digitalRead(BUT_RIGHT) == 1 && but_flag[2] == 1) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.circle(20, 63, 10);
      but_flag[2] = 0;
    }

    if (digitalRead(BUT2) == 0 && but_flag[3] == 0) {//4
      TFTscreen.fill(0, 0, 0);
      TFTscreen.circle(15, 38, 10);
      but_flag[3] = 1;
    }
    if (digitalRead(BUT2) == 1 && but_flag[3] == 1) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.circle(15, 38, 10);
      but_flag[3] = 0;
    }

    if (digitalRead(BUT1) == 0 && but_flag[4] == 0) {//5
      TFTscreen.fill(0, 0, 0);
      TFTscreen.circle(15, 13, 10);
      but_flag[4] = 1;
    }
    if (digitalRead(BUT1) == 1 && but_flag[4] == 1) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.circle(15, 13, 10);
      but_flag[4] = 0;
    }

    if (digitalRead(BUT_OK) == 0 && but_flag[5] == 0) {//6
      TFTscreen.fill(0, 0, 0);
      TFTscreen.circle(140, 113, 10);
      but_flag[5] = 1;
    }
    if (digitalRead(BUT_OK) == 1 && but_flag[5] == 1) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.circle(140, 113, 10);
      but_flag[5] = 0;
    }

    if (digitalRead(BUT_DOWN) == 0 && but_flag[6] == 0) {//7
      TFTscreen.fill(0, 0, 0);
      TFTscreen.circle(140, 88, 10);
      but_flag[6] = 1;
    }
    if (digitalRead(BUT_DOWN) == 1 && but_flag[6] == 1) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.circle(140, 88, 10);
      but_flag[6] = 0;
    }

    if (digitalRead(BUT_UP) == 0 && but_flag[7] == 0) {//8
      TFTscreen.fill(0, 0, 0);
      TFTscreen.circle(140, 63, 10);
      but_flag[7] = 1;
    }
    if (digitalRead(BUT_UP) == 1 && but_flag[7] == 1) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.circle(140, 63, 10);
      but_flag[7] = 0;
    }

    if (digitalRead(BUT_LANDING) == 0 && but_flag[8] == 0) {//9
      TFTscreen.fill(0, 0, 0);
      TFTscreen.circle(145, 38, 10);
      but_flag[8] = 1;
    }
    if (digitalRead(BUT_LANDING) == 1 && but_flag[8] == 1) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.circle(145, 38, 10);
      but_flag[8] = 0;
    }

    if (digitalRead(BUT_TAKEOFF) == 0 && but_flag[9] == 0) {//10
      TFTscreen.fill(0, 0, 0);
      TFTscreen.circle(145, 13, 10);
      but_flag[9] = 1;
    }
    if (digitalRead(BUT_TAKEOFF) == 1 && but_flag[9] == 1) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.circle(145, 13, 10);
      but_flag[9] = 0;
    }

    sw_old_flag[0] = sw_flag[0];
    sw_flag[0] = 39 - map(analogReadStab(TW_LEFT), 0, 1023, 0, 39);
    if (sw_flag[0] != sw_old_flag[0]) {
      TFTscreen.noFill();
      TFTscreen.stroke(255, 255, 255);
      TFTscreen.circle(35 + sw_old_flag[0], 113, 3);
      TFTscreen.stroke(0, 0, 0);
      TFTscreen.line(35, 113, 74, 113);
      TFTscreen.circle(35 + sw_flag[0], 113, 3);
    }

    sw_old_flag[1] = sw_flag[1];
    sw_flag[1] = 39 - map(analogReadStab(TW_RIGHT), 0, 1023, 0, 39);
    if (sw_flag[1] != sw_old_flag[1]) {
      TFTscreen.noFill();
      TFTscreen.stroke(255, 255, 255);
      TFTscreen.circle(84 + sw_old_flag[1], 113, 3);
      TFTscreen.stroke(0, 0, 0);
      TFTscreen.line(84, 113, 123, 113);
      TFTscreen.circle(84 + sw_flag[1], 113, 3);
    }

    //TFTscreen.line(35, 63, 74, 63);
    //TFTscreen.line(84, 63, 123, 63);
    but_flag[11] = but_flag[10];
    if (digitalRead(SW1) == 0 && but_flag[10] == 0) {//10
      but_flag[10] = 1;
    }
    if (digitalRead(SW1) == 1 && but_flag[10] == 1) {
      but_flag[10] = 0;
    }

    but_flag[13] = but_flag[12];
    if (digitalRead(SW2) == 0 && but_flag[12] == 0) {//10
      but_flag[12] = 1;
    }
    if (digitalRead(SW2) == 1 && but_flag[12] == 1) {
      but_flag[12] = 0;
    }

    but_flag[14] = but_flag[15];
    if (digitalRead(TOGGLE_LEFT_UP1) == 0) {
      but_flag[15] = 2;
    }
    else if (digitalRead(TOGGLE_LEFT_DOWN1) == 0) {
      but_flag[15] = 0;
    }
    else {
      but_flag[15] = 1;
    }
    if (but_flag[14] != but_flag[15]) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.stroke(255, 255, 255);
      TFTscreen.circle(44, 10 + but_flag[14] * 10, 3);
      TFTscreen.stroke(0, 0, 0);
      TFTscreen.fill(0, 0, 0);
      TFTscreen.line(44, 10, 44, 30);
      TFTscreen.line(43, 10, 46, 10);
      TFTscreen.line(43, 20, 46, 20);
      TFTscreen.line(43, 30, 46, 30);
      TFTscreen.circle(44, 10 + but_flag[15] * 10, 3);
    }

    but_flag[16] = but_flag[17];
    but_flag[17] = digitalRead(TOGGLE_LEFT);
    if (but_flag[16] != but_flag[17]) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.stroke(255, 255, 255);
      TFTscreen.circle(64, 10 + but_flag[16] * 20, 3);
      TFTscreen.stroke(0, 0, 0);
      TFTscreen.fill(0, 0, 0);
      TFTscreen.line(64, 10, 64, 30);
      TFTscreen.line(63, 10, 66, 10);
      TFTscreen.line(63, 30, 66, 30);
      TFTscreen.circle(64, 10 + but_flag[17] * 20, 3);
    }

    but_flag[18] = but_flag[19];
    but_flag[19] = digitalRead(TOGGLE_RIGHT);
    if (but_flag[18] != but_flag[19]) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.stroke(255, 255, 255);
      TFTscreen.circle(93, 10 + but_flag[18] * 20, 3);
      TFTscreen.stroke(0, 0, 0);
      TFTscreen.fill(0, 0, 0);
      TFTscreen.line(93, 10, 93, 30);
      TFTscreen.line(92, 10, 95, 10);
      TFTscreen.line(92, 30, 95, 30);
      TFTscreen.circle(93, 10 + but_flag[19] * 20, 3);
    }

    but_flag[20] = but_flag[21];
    if (digitalRead(TOGGLE_RIGHT_UP1) == 0) {
      but_flag[21] = 2;
    }
    else if (digitalRead(TOGGLE_RIGHT_DOWN1) == 0) {
      but_flag[21] = 0;
    }
    else {
      but_flag[21] = 1;
    }
    if (but_flag[20] != but_flag[21]) {
      TFTscreen.fill(255, 255, 255);
      TFTscreen.stroke(255, 255, 255);
      TFTscreen.circle(113, 10 + but_flag[20] * 10, 3);
      TFTscreen.stroke(0, 0, 0);
      TFTscreen.fill(0, 0, 0);
      TFTscreen.line(113, 10, 113, 30);
      TFTscreen.line(112, 10, 115, 10);
      TFTscreen.line(112, 20, 115, 20);
      TFTscreen.line(112, 30, 115, 30);
      TFTscreen.circle(113, 10 + but_flag[21] * 10, 3);
    }

    sw_old_flag[2] = sw_flag[2];
    sw_old_flag[3] = sw_flag[3];
    sw_flag[2] = map(JOY_LEFT_X.compute(analogRead(J_LEFT_X)), ERR_LEFT_X_MIN, ERR_LEFT_X_MAX, 0, 39);
    sw_flag[3] = map(JOY_LEFT_Y.compute(analogRead(J_LEFT_Y)), ERR_LEFT_Y_MIN, ERR_LEFT_Y_MAX, 0, 39);
    if (sw_flag[2] != sw_old_flag[2] || sw_flag[3] != sw_old_flag[3] || but_flag[10] != but_flag[11]) {
      TFTscreen.stroke(255, 255, 255);
      if (but_flag[10] == 0) {
        TFTscreen.fill(255, 255, 255);
        TFTscreen.circle(35 + sw_old_flag[2], 44 + sw_old_flag[3], 3);
        TFTscreen.noFill();
      }
      if (but_flag[10] == 1) {
        TFTscreen.fill(255, 255, 255);
      }
      TFTscreen.circle(35 + sw_old_flag[2], 44 + sw_old_flag[3], 3);
      TFTscreen.stroke(0, 0, 0);
      TFTscreen.line(35, 63, 74, 63);
      TFTscreen.line(54, 44, 54, 82);
      if (but_flag[10] == 1) {
        TFTscreen.fill(0, 0, 0);
      }
      TFTscreen.circle(35 + sw_flag[2], 44 + sw_flag[3], 3);
    }

    sw_old_flag[4] = sw_flag[4];
    sw_old_flag[5] = sw_flag[5];
    sw_flag[4] = map(JOY_RIGHT_X.compute(analogRead(J_RIGHT_X)), ERR_RIGHT_X_MIN, ERR_RIGHT_X_MAX, 0, 39);
    sw_flag[5] = map(JOY_RIGHT_Y.compute(analogRead(J_RIGHT_Y)), ERR_RIGHT_Y_MIN, ERR_RIGHT_Y_MAX, 0, 39);
    if (sw_flag[4] != sw_old_flag[4] || sw_flag[5] != sw_old_flag[5] || but_flag[12] != but_flag[13]) {
      TFTscreen.stroke(255, 255, 255);
      if (but_flag[12] == 0) {
        TFTscreen.fill(255, 255, 255);
        TFTscreen.circle(84 + sw_old_flag[4], 44 + sw_old_flag[5], 3);
        TFTscreen.noFill();
      }
      if (but_flag[12] == 1) {
        TFTscreen.fill(255, 255, 255);
      }
      TFTscreen.circle(84 + sw_old_flag[4], 44 + sw_old_flag[5], 3);
      TFTscreen.stroke(0, 0, 0);
      TFTscreen.line(84, 63, 123, 63);
      TFTscreen.line(103, 44, 103, 82);
      if (but_flag[12] == 1) {
        TFTscreen.fill(0, 0, 0);
      }
      TFTscreen.circle(84 + sw_flag[4], 44 + sw_flag[5], 3);
    }
  }
}

void read_sensor_quadcopter1() {
  TFT.rect(xStart, yStart, width, height);
  TFT.rect(xStart, yStart, width, height);
  TFT.rect(xStart, yStart, width, height);
  TFT.rect(xStart, yStart, width, height);
  TFT.rect(xStart, yStart, width, height);
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
