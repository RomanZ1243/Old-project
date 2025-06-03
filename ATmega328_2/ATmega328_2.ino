boolean flag;
boolean led1;

void setup() {
  pinMode(9, OUTPUT);
  pinMode(8, INPUT_PULLUP);
}

void loop() {
  if (flag == 0) {
    if (digitalRead(8) == 0) {
      led1 = !led1;
      digitalWrite(9, led1);
      flag = 1;
    }
  }
  if (flag == 1) {
    if (digitalRead(8) == 1) {
      flag = 0;
    }
  }
}
