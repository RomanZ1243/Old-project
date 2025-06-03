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

int kp = 1.2;
float kk = 0;
int d = 25;
int black = 975;
int mid_sp = 75;
int max_sp = 25;
int flag;
int i;
int err;

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
  err = analogRead(D3) - analogRead(D6);
  Serial.print(err);
  Serial.print(" ");
  Serial.print(analogRead(D3));
  Serial.print(" ");
  Serial.print(mid_sp + ((kp * err) + kk * pow(err, 3)));
  Serial.print(" ");
  Serial.println(mid_sp - ((kp * err) + kk * pow(err, 3)));
  digitalWrite(L1, LOW);
  digitalWrite(R1, LOW);
  analogWrite(L2, mid_sp + ((kp * err) + kk * pow(err, 3)));
  analogWrite(R2, mid_sp - ((kp * err) + kk * pow(err, 3)));
}
