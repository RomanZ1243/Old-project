int i = 1;
boolean g1;
boolean g2;
boolean g3;
boolean g4;
void setup() {
 pinMode(4,INPUT);
 pinMode(8,INPUT);
 pinMode(5,OUTPUT); 
 pinMode(6,OUTPUT); 
 pinMode(12,OUTPUT); 
 pinMode(10,OUTPUT); 
 Serial.begin(9600);
}

void loop() {
  delay(150);
  if(digitalRead(8) == 0) {
    i++;
  }
  if(i>4) {
    i = 1;
  }
  switch(i) {
    
    case 1:
    delay(150);
    g1 = !g1;
    if (digitalRead(4) == 0) {
      digitalWrite(5, g1);
    }
    break;

    case 2:
    delay(150);
    g2 = !g2;
    if (digitalRead(4) == 0) {
      digitalWrite(6, g2);
    }
    break;

    case 3:
    delay(150);
    g3 = !g3;
    if (digitalRead(4) == 0) {
      digitalWrite(12, g3);
    }
    break;

    case 4:
    delay(150);
    g4 = !g4;
    if (digitalRead(4) == 0) {
      digitalWrite(10, g4);
    }
    break;
    Serial.println(i);
  }
}
