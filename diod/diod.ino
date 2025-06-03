void setup() {
  pinMode(4, INPUT_PULLUP); // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  Serial.println(analogRead(A0));
  /*if (digitalRead(4) == 1) {
    Serial.println("-+");
  }
  else {
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    if (digitalRead(4) == 0) {
      Serial.println("+-");
    }
    else {
      Serial.println("error");
    }
  }*/
}
