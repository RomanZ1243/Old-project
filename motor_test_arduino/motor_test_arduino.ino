#define IR_L 2
#define IR_R 3
#define enc_L 8
#define enc_R 9
#define HC_TRIG 10
#define HC_ECHO 11

#define H1 4
#define E1 5
#define H2 6
#define E2 7

#include <Servo.h>
#include <NewPing.h>

Servo myservo;
NewPing sonar(HC_TRIG, HC_ECHO, 100);

int pos = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(12);
  pinMode(IR_L, INPUT_PULLUP);
  pinMode(IR_R, INPUT_PULLUP);
  pinMode(enc_L, INPUT_PULLUP);
  pinMode(enc_R, INPUT_PULLUP);
  pinMode(H1, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(H2, OUTPUT);
  pinMode(E2, OUTPUT);
}

void loop() {
  Serial.print(digitalRead(IR_L));
  Serial.print(" ");
  Serial.print(digitalRead(IR_R));
  Serial.print(" ");
  Serial.print(digitalRead(enc_L));
  Serial.print(" ");
  Serial.print(digitalRead(enc_R));
  Serial.print(" ");
  Serial.println(sonar.ping_cm());
}
