#define L1 10
#define L2 11
#define R1 6
#define R2 9

#include <IRremote.h>

IRrecv irrecv(2);
decode_results results;

void setup() {
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  irrecv.enableIRIn();
  //Serial.begin(9600);
}

void loop() {
  if ( irrecv.decode( &results )) { // если данные пришли
    switch ( results.value ) {
      case 0x770:
        analogWrite(L1, 0);
        analogWrite(L2, 50);
        analogWrite(R1, 0);
        analogWrite(R2, 50);
        digitalWrite(13, HIGH);
        break;
      case 0x2F0:
        analogWrite(L1, 0);
        analogWrite(L2, 50);
        analogWrite(R1, 0);
        analogWrite(R2, 0);
        break;
      case 0xF70:
        analogWrite(L1, 50);
        analogWrite(L2, 0);
        analogWrite(R1, 50);
        analogWrite(R2, 0);
        digitalWrite(13, LOW);
        break;
      case 0xAF0:
        analogWrite(L1, 0);
        analogWrite(L2, 0);
        analogWrite(R1, 0);
        analogWrite(R2, 50);
        break;
      case 0x3F0:
        analogWrite(L1, 0);
        analogWrite(L2, 0);
        analogWrite(R1, 0);
        analogWrite(R2, 0);
        break;
    }
    irrecv.resume(); // принимаем следующую команду
  }
  /*analogWrite(L1, 0);
    analogWrite(L2, 200);
    analogWrite(R1, 0);
    analogWrite(R2, 200);*/
}
