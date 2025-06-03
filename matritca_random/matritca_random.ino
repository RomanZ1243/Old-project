#define R5 1
#define R7 2
#define C2 3
#define C3 4
#define R8 5
#define C5 7
#define R6 6
#define R3 8
#define C8 9
#define C7 10
#define R2 11
#define C1 A1
#define R4 A5
#define C6 A3
#define C4 A4
#define R1 A2
byte z1[8]={0b00000000,
            0b00000000,
            0b00000000,
            0b00100000,
            0b01000000,
            0b11111100,
            0b00000000,
            0b00000000};
byte z2[8]={0b00000000,
            0b00000000,
            0b00000110,
            0b01001010,
            0b01001010,
            0b01001010,
            0b00110010,
            0b00000000};
  int sed[8] = {C1,C2,C3,C4,C5,C6,C7,C8};
  void setup() {
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(R3,OUTPUT);
  pinMode(R4,OUTPUT);
  pinMode(R5,OUTPUT);
  pinMode(R6,OUTPUT);
  pinMode(R7,OUTPUT);
  pinMode(R8,OUTPUT);
  pinMode(C1,OUTPUT);
  pinMode(C2,OUTPUT);
  pinMode(C3,OUTPUT);
  pinMode(C4,OUTPUT);
  pinMode(C5,OUTPUT);
  pinMode(C6,OUTPUT);
  pinMode(C7,OUTPUT);
  pinMode(C8,OUTPUT);
}

void loop() {
  for(int i = 0;i<8;i++) { 
  digitalWrite(C1,HIGH);
  digitalWrite(C2,HIGH);
  digitalWrite(C3,HIGH);
  digitalWrite(C4,HIGH);
  digitalWrite(C5,HIGH);
  digitalWrite(C6,HIGH);
  digitalWrite(C7,HIGH);
  digitalWrite(C8,HIGH);
  ret(z2[i]);
  digitalWrite(sed[i],LOW);
  delay(2);
  }
}
  void ret(byte X) {
    digitalWrite(R1,X>>7&1);
    digitalWrite(R2,X>>6&1);
    digitalWrite(R3,X>>5&1);
    digitalWrite(R4,X>>4&1);
    digitalWrite(R5,X>>3&1);
    digitalWrite(R6,X>>2&1);
    digitalWrite(R7,X>>1&1);
    digitalWrite(R8,X>>0&1);
  }
