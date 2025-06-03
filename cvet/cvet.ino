int flag = 0;

void setup() {
  pinMode(5, INPUT_PULLUP);
  pinMode(8, OUTPUT);
}


void loop() {
  if (flag == 0) {
    if (digitalRead(5) == 0) {
      digitalWrite(8, HIGH);    
       if (digitalRead(5) == 1) {
        flag = 1;
       }
    }
  }

  if (flag == 1) {
    if (digitalRead(5) == 0) {
      digitalWrite(8, LOW);      
       if (digitalRead(5) == 1) {
        flag = 0;
       }  
    }
  }
}
