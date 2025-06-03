#include "Dragster.h"
#include "Octoliner.h"
#include "PID_dragster.h"
 
Dragster robot(MMAX_16_OHM);
Octoliner octoliner;
 
int lineData[8];
 
float speed = 0.4;
float KP = 2.5;
 
double output;
PID regulator(&output, KP, 0, 0);
 
void setup() {
  robot.begin();
  octoliner.begin();
  octoliner.setSensitivity(208);
}
 
void loop() {
  for (int i = 0; i < 8; i++) {
    lineData[i] = octoliner.analogRead(i);
  }
  double error = octoliner.trackLine(lineData);
  regulator.compute(error);
  robot.driveF(speed * (1 - output), speed * (1 + output));
}
