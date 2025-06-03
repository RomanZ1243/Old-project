#include "IRremote.h"

IRrecv irrecv(2); // указываем вывод, к которому подключен приемник

decode_results results;

void setup() {
  irrecv.enableIRIn(); // запускаем прием
}

void loop() {
  if ( irrecv.decode( &results )) { // если данные пришли
    switch ( results.value ) {
    case 0x770:
        digitalWrite( 13, HIGH );
        break;
    case 0xF70:
        digitalWrite( 13, LOW );
        break;
    }    
    irrecv.resume(); // принимаем следующую команду
  }
}
