void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
}
void loop() {
  if (Serial.available()) {
    String str = Serial.readString();
    Serial.println(str);
  }
}
