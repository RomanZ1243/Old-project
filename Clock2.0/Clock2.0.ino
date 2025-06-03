#define CLK 3
#define DIO 2
#define but1 4
#define but2 5
#define but3 6
#define led1 7
#define buz 8

#include "GyverTM1637.h"
GyverTM1637 disp(CLK, DIO);

long previousMillis = 0;
long previousMillis1 = 0;
long interval = 1000;
int a;
boolean flag = 1;
long b;

void setup() {
  Serial.begin(9600);
  disp.clear();
  disp.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
  pinMode(but1, INPUT_PULLUP);
  pinMode(but2, INPUT_PULLUP);
  pinMode(but3, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
}

void loop() {
  /*if(millis() - previousMillis > interval) {
    previousMillis = millis();
    a++;
    }*/
  if (millis() % 500 == 0) {
    
    b++;
    if (flag == 0) {
      flag = 1;
    }
    else if (flag == 1) {
      flag = 0;
    }
    if (b % 2 == 0) {
      a++;
    }
    disp.point(flag);
    disp.displayInt(a);
    Serial.println(a);
    //previousMillis1 = millis();
  }

}
