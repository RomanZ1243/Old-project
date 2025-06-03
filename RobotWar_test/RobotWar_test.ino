#include <IBusBM.h>
IBusBM IBus;    // IBus object

void setup() {
  IBus.begin(Serial);    // iBUS object connected to serial0 RX pin
}

void loop() {
  IBus.loop();
  Serial.print(IBus.readChannel(0));
  Serial.print(" ");
  Serial.print(IBus.readChannel(1));
  Serial.print(" ");
  Serial.print(IBus.readChannel(2));
  Serial.print(" ");
  Serial.print(IBus.readChannel(3));
  Serial.print(" ");
  Serial.print(IBus.readChannel(4));
  Serial.print(" ");
  Serial.print(IBus.readChannel(5));
  Serial.print(" ");
  Serial.print(IBus.readChannel(6));
  Serial.print(" ");
  Serial.println(IBus.readChannel(7));
  delay(20);
}
