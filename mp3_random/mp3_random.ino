#include "SoftwareSerial.h"            // библиотека для для обмена данными 
#include <DFPlayer_Mini_Mp3.h> // подключаем библиотеку для DFPlayer Mini

SoftwareSerial mySerial(2, 3);        // RX, TX

int x;
int flag;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  mp3_set_serial(mySerial); // включаем передачу данных с DFPlayer
  mp3_set_volume(10);        // устанавливаем громкость от 0 до 30
  mp3_set_EQ(0);                  // устанавливаем эквалайзер от 0 до 5
  randomSeed(analogRead(0));
  pinMode(4, INPUT_PULLUP);
}

void loop() {
  if (flag == 0) {
    if (digitalRead(4) == 0) {
      x = random(1, 6);
      flag = 1;
    }
  }
  if (flag == 1) {
    mp3_play(x);
    Serial.println(x);
    delay(3000);
    flag = 0;
  }
}
