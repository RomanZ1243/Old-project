#define nob 4
#define enc1 5
#define enc2 6
#define R 7
#define G 8
#define B A0

#include <Servo.h>
Servo myservo;
Servo myservo2;
int x = 1;

void setup() {
  myservo.attach(9);// put your setup code here, to run once:
  myservo2.attach(10);
  attachInterrupt(3, my, FALLING);
  Serial.begin(9600);
  pinMode(4, INPUT_PULLUP);
}

void loop() {
  if (x > 4) {
    x = 1;
  }
  //myservo.write(); // put your main code here, to run repeatedly:
  Serial.println(x);
  delay(100);
}

void my() {
  x++;
}
