#include "SoftwareSerial.h"            // библиотека для для обмена данными 
#include <DFPlayer_Mini_Mp3.h> // подключаем библиотеку для DFPlayer Mini

SoftwareSerial mySerial(7, 8);        // RX, TX

int x;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  mp3_set_serial(mySerial); // включаем передачу данных с DFPlayer
  mp3_set_volume(2);        // устанавливаем громкость от 0 до 30
  mp3_set_EQ(0);                  // устанавливаем эквалайзер от 0 до 5
  randomSeed(analogRead(0));
}

void loop() {
  //x = random(1, 6);
  mp3_play(1);
  //Serial.println(x);
  delay(3000);
}
