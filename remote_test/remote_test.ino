#define x1 A7
#define y1 A0
#define x2 A3
#define y2 A2

#include <GyverJoy.h>

GyverJoy jx1;
GyverJoy jy1;
GyverJoy jx2;
GyverJoy jy2;
RF24 radio(23, 53);
TFT TFTscreen = TFT(cs, dc, rst);


void setup() {
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
  Serial.begin(9600);
}

void loop() {
  Serial.print(jx1.compute(analogRead(x1)));
  Serial.print(jx2.compute(analogRead(x2)));
  Serial.print(jy1.compute(analogRead(y1)));
  Serial.println(jy2.compute(analogRead(y2)));

}
