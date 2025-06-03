byte b;
void setup() {
pinMode(2,OUTPUT);  
Serial.begin(9600);

}

void loop() {
byte a = random(0,256);
byte b = random(0,256);
byte c = ~b;
if(a==c){
Serial.println(a);
Serial.println(b);
Serial.println(" => ");
Serial.println(a,BIN);
Serial.println(b,BIN);
Serial.println("yyyeeesss");
digitalWrite(2,HIGH);
delay(3000);
digitalWrite(2,LOW); 
  }
delay(10);
}
