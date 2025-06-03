#include <Servo.h>

Servo myservo;  // create servo object to control a servo

#include <IRremote.h>
 int RECV_PIN = 12;
 IRrecv irrecv(RECV_PIN);
 decode_results results;

void setup() {
  myservo.attach(3);
  irrecv.enableIRIn();// attaches the servo on pin 9 to the servo object
}

void loop() {   // scale it to use it with the servo (value between 0 and 180)
if ( irrecv.decode( &results )) { // если данные пришли
switch ( results.value ) {
case 0xFF6897:
 myservo.write(20);
break;
case 0xFF9867:
 myservo.write(40);
break;
case 0xFFB04F:
 myservo.write(60);
break;
case 0xFF30CF:
 myservo.write(80);
break;
case 0xFF18E7:
 myservo.write(100);
break;
case 0xFF7A85:
 myservo.write(120);
break;
case 0xFF10EF:
 myservo.write(140);
break;
case 0xFF38C7:
 myservo.write(160);
break;
case 0xFF5AA5:
 myservo.write(180);
break;

} 
irrecv.resume(); // принимаем следующую команду
}// waits for the servo to get there
}
