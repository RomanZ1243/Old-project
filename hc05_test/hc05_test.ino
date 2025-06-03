String myString;

void setup() {
  Serial.begin(9600);


}

void loop() {
  if (Serial.available()) {
    myString = Serial.readString();
    myString.trim();
    if (myString.equals("Arduino")) {
      Serial.println(1);
    }
    else {
      Serial.println(0);
    }
  }
}
