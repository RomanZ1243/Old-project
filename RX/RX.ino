#include <Servo.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;

RF24 radio(9, 10);  // "создать" модуль на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

void setup() {
  Serial.begin(9600);         // открываем порт для связи с ПК
  myservo1.attach(2);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(3);
  myservo3.attach(4);
  myservo4.attach(5);
  pinMode(2, OUTPUT);
  radio.begin();              // активировать модуль
  radio.setAutoAck(1);        // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();   // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);   // размер пакета, в байтах

  radio.openReadingPipe(1, address[0]);   // хотим слушать трубу 0
  radio.setChannel(0x60);     // выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX);   // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp();        // начать работу
  radio.startListening(); // начинаем слушать эфир, мы приёмный модуль
}

void loop() {
  byte pipeNo; 
  int gotByte;
  while (radio.available(&pipeNo)) {        // слушаем эфир со всех труб
    radio.read(&gotByte, sizeof(gotByte));  // чиатем входящий сигнал
    Serial.println(gotByte);
  }
  gotByte = map(gotByte, 0, 1023, 800, 2300);
  myservo1.writeMicroseconds(gotByte);                  // sets the servo position according to the scaled value
  myservo2.writeMicroseconds(gotByte);
  myservo3.writeMicroseconds(gotByte);
  myservo4.writeMicroseconds(gotByte);
  //Serial.println(gotByte);
  delay(20);
}
