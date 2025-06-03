int IN1=2;
int IN2=4;
int IN3=7;
int IN4=8;
int ENA=5;
int ENB=10;
void setup()
{
  
}
void loop(){
 digitalWrite(IN1,HIGH);
 digitalWrite(IN2,LOW);
 analogWrite(ENA,200);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);
 analogWrite(ENB,200);
}
