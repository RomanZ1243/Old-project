#include "MPU6050.h"
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
void setup() {
  Wire.begin();
  Serial.begin(9600);
  mpu.initialize();
  // состояние соединения
  Serial.println(mpu.testConnection() ? "MPU6050 OK" : "MPU6050 FAIL");
  delay(1000);
}
void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax = map(ax, -16384, 16384, -180, 180);
  Serial.println(analogReadStab(ax)); Serial.print('\t');
  //Serial.print(ay); Serial.print('\t');
  //Serial.println(az); Serial.print('\t');
  /*Serial.print(gx); Serial.print('\t');
  Serial.print(gy); Serial.print('\t');
  Serial.println(gz);*/
  delay(5);
}


int analogReadStab(byte analogPin) {
  long sum = 0;
  for (int p = 0; p <= 255; p++) {
    sum += analogRead(analogPin);
  }
  sum = sum >> 8;
  return sum;
}
