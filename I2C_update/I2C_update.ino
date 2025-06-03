#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();


void setup() {
  // Robojax.com I2C address update 20181206
  lox.begin(0x31);// put any address between 0x29 to 0x7F 
}

void loop(){
  
}

 
 
