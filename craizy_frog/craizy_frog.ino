void setup() {
 pinMode(4,OUTPUT);
}

void loop() {
tone(4,293,350);  
delay(450);
tone(4,349,350);  
delay(450);
tone(4,293,200);  
delay(250);
tone(4,293,100);
delay(150);
tone(4,392,150);  
delay(250);
tone(4,293,150);  
delay(250);
tone(4,261,150);  
delay(250);
tone(4,293,150);  
delay(1000);
}
