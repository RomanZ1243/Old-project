#define D1 A0
#define D2 A1
#define D3 A2
#define D4 A3
#define D5 A4
#define D6 A5
#define D7 A6
#define D8 A7
#define DL 2
#define DR 3

#define L1 9
#define L2 6
#define R1 11
#define R2 10

int k;
int d = 50;
int black1 = 975;
int black2 = 975;
int black3 = 975;
int black4 = 975;
int black5 = 975;
int black6 = 975;
int black7 = 975;
int black8 = 975;
int max_sp = 255;
int flag;

void setup() {
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(DL, INPUT_PULLUP);
  pinMode(DR, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(DL) == 1) {
    k = -5;
  }
  if (analogRead(D8) > black1) {
    k = -4;
  }
  if (analogRead(D8) > black1 && analogRead(D7) > black2) {
    k = -3;
  }
  if (analogRead(D7) > black2 && analogRead(D6) > black3) {
    k = -2;
  }
  if (analogRead(D6) > black3 && analogRead(D5) > black4) {
    k = -1;
  }

  if (analogRead(D5) > black4 && analogRead(D4) > black5) {
    k = 0;
  }

  if (analogRead(D4) > black5 && analogRead(D3) > black6) {
    k = 1;
  }
  if (analogRead(D3) > black6 && analogRead(D2) > black7) {
    k = 2;
  }
  if (analogRead(D2) > black7 && analogRead(D1) > black8) {
    k = 3;
  }
  if (analogRead(D1) > black8) {
    k = 4;
  }
  if (digitalRead(DR) == 1) {
    k = 5;
  }
  digitalWrite(L1, LOW);
  digitalWrite(R1, LOW);
  if (k < 0) {//если видит левый датчик, робот поворачивается налево
    analogWrite(L2, max_sp + (k * d));
    analogWrite(R2, max_sp);
  }
  if (k > 0) {//если видит правый датчик, робот поворачивается направо
    analogWrite(L2, max_sp);
    analogWrite(R2, max_sp - (k * d));
  }
  if (k == 0) { //если линия посередине, робот едет прямо
    analogWrite(L2, max_sp);
    analogWrite(R2, max_sp);
  }
  Serial.println(k);
}
