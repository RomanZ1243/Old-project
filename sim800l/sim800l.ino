#include <SoftwareSerial.h>
SoftwareSerial SIM800(8, 9);
void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  SIM800.begin(9600);
  SIM800.println("AT");
}

void loop() {
  if(SIM800.available()){
    Serial.write(SIM800.read());
  }
if(Serial.available()){
    SIM800.write(Serial.read());
  }
}
