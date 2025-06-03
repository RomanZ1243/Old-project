#include <LineDriver.h>
#include <SPI.h>
#include <SPI_Bus.h>
SPI_Bus reg(_24bit, A1, MSBFIRST); 

void setup(){
  Serial.begin(9600);
  reg.setSelectionPolicy(SPI_Bus::SELECT_BEFORE);
}

void loop(){
  static uint32_t last_input_states = 0;
  /* Читаем наши 24 бита разом. В C++ нет типов данных для 24-битных чисел,
   * поэтому используем read32bits(), который считает столько бит,
   * сколько мы указали при создании объекта reg (24 бита), но вернёт их
   * одним 32-битным значением.
   */
  uint32_t states = reg.read32bits();
  if (states != last_input_states){
    uint32_t changed = states ^ last_input_states;
    last_input_states = states;
    for (int i = 0; i < reg.bandwidth() * 8; ++i){
      /* А вот тут проверяем только нужные нам входы */
      if ((i >= 0 && i <= 23) && (changed & 1)){
        Serial.print("#");
        Serial.print(i);
        Serial.print(" -> ");
        Serial.println(states & 1);
      }
      changed >>= 1;
      states >>= 1;
    }
  }
}
