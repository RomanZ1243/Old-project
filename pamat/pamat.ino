int x;//уровень игры
int n;
int i;
byte demo[10] = {10, 23, 45, 76, 74, 82, 91, 48, 14, 8};
int a = 1;
void LED(int c) {
  off();
  while (n < 10) {
    n++;
    delay(100);
    while (i < n) {
      Serial.println(i);
      digitalWrite(i, HIGH);
      delay(500);
      digitalWrite(i, LOW);
      delay(1000);
      i++;
      if (i == 10) {
        Serial.println("всё");
      }
    }
  }
}
void off() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}
void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(A0));
}
void loop() {
  digitalWrite(12, LOW);
  if (a == 1) {         //
    Serial.println("нажмите любую кнопку");
    if (digitalRead(7) == 0 || digitalRead(8) == 0 || digitalRead(9) == 0 || digitalRead(10) == 0) {
      a = 2;
    }
    if (a == 2) {
      while (i < 10) {
        demo[i] = random(2, 6);
        while (n < 10) {
          n++;
          delay(250);
          while (i < n) {
            delay(250);
            LED(i);
            delay(250);
            off();
          }

        }
        if (a == 3) {
          i = 0;
          a = 2;
        }
      }
    }
  }
}
