#include <matrix.h>
Matrix mtrx;

void setup() {
  Serial.begin(9600);
  mtrx.full();
}

void loop() {
  mtrx.update();
}
