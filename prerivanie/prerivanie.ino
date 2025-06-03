int led = 1;
void setup() {
 pinMode(3, INPUT_PULLUP);
  pinMode(8, OUTPUT);

  attachInterrupt(1,blink,RISING);
}

void loop(){
  digitalWrite(8,led);
  delay(100);
}

void blink() {
 led = !led;
 delay(200);// put your main code here, to run repeatedly:

}
