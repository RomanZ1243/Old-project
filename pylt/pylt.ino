#include "IRremote.h"
 
IRrecv irrecv(12); // указываем вывод, к которому подключен приемник
 
decode_results results;

int IN1=2;
int IN2=4;
int IN3=7;
int IN4=8;
int ENA=5;
int ENB=10;
 
void setup() {
irrecv.enableIRIn(); // запускаем прием
}
 
void loop() {
if ( irrecv.decode( &results )) { // если данные пришли
switch ( results.value ) {
case 0xFF629D:
 digitalWrite(IN1,HIGH);
 digitalWrite(IN2,LOW);
 analogWrite(ENA,100);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);
 analogWrite(ENB,100);
break;
case 0xFFA857:
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,HIGH);
 analogWrite(ENA,100);
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
 analogWrite(ENB,100);
break;
} 
irrecv.resume(); // принимаем следующую команду
}
}
