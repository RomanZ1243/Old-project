int big = 0;
int little = 0;
int x = 1;
int i;
unsigned long timing;

void setup() {
 pinMode(2,OUTPUT);//красный
 pinMode(3,OUTPUT);//зеленый
 pinMode(4,OUTPUT);//синий
 pinMode(6,INPUT_PULLUP);
 Serial.begin(9600);
}

void loop() {
  i = 2;
 if(x == 1){
 if(digitalRead(6) == 0){
  i = 4;
  timing=timing+1.7;
  delay(1);
  if(digitalRead(6) == 1){
   x = 2;
  }
   }
 }
 if(x == 2){
 if(timing < 2000){
  little=little+1;
  timing=timing*0.1;
  Serial.println ("Крупногабаритных:" + String(big));
  Serial.println ("Малогабаритных:" + String(little));
  Serial.println("ДЛИНА:" + String(timing) + "см"); 
  Serial.println("Малогабаритный");
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  delay(300);
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  timing = 0;
  x = 1;
 }
 if(timing > 2000){
  big=big+1;
  timing=timing*0.1;
  Serial.println ("Крупногабаритных:" + String(big));
  Serial.println ("Малогабаритных:" + String(little));
  Serial.println("ДЛИНА:" + String(timing) + "см"); 
  Serial.println("Крупногабаритный");
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  delay(300);
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  timing = 0;
  x = 1;
 }
 }
switch(i){
case 2:
digitalWrite(2,HIGH);
digitalWrite(3,LOW);
digitalWrite(4,LOW);
break;
case 3:
digitalWrite(2,LOW);
digitalWrite(3,HIGH);
digitalWrite(4,LOW);
break;
case 4:
digitalWrite(2,LOW);
digitalWrite(3,LOW);
digitalWrite(4,HIGH);
break;
  }
}
