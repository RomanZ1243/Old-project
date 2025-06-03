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

float error1 = 0;
float Kp = 22;
float Ki = 0.8;
float Kd = 40;
float kk = 0.005;
//float Dt = 0.1;
float P;
float I;
float D;
float PID_value = 0;
float previous_error = 0;
float previous_I = 0;
int mid_sp = 125;
int black = 975;


void setup()
{
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(DL, INPUT_PULLUP);
  pinMode(DR, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (analogRead(D8) > black) {
    error1 = -4;
  }
  if (analogRead(D1) > black) {
    error1 = 4;
  }
  if (analogRead(D8) > black && analogRead(D7) > black) {
    error1 = -3;
  }
  if (analogRead(D7) > black && analogRead(D6) > black) {
    error1 = -2;
  }
  if (analogRead(D6) > black && analogRead(D5) > black) {
    error1 = -1;
  }
  if (analogRead(D5) > black && analogRead(D4) > black) {
    error1 = 0;
  }
  if (analogRead(D4) > black && analogRead(D3) > black) {
    error1 = 1;
  }
  if (analogRead(D3) > black && analogRead(D2) > black) {
    error1 = 2;
  }
  if (analogRead(D2) > black && analogRead(D1) > black) {
    error1 = 3;
  }
  if (digitalRead(DL) == 1) {
    error1 = -5;
  }
  if (digitalRead(DR) == 1) {
    error1 = 5;
  }

  P = error1;
  I = I + error1;
  D = error1 - previous_error;
  //.println(I);
  PID_value = (Kp * P) + (Ki * I) + (Kd * D) + (kk * pow(error1,3));
  Serial.println(PID_value);
  I = error1;
  previous_error = error1;

  /*P = error1;
    I = I + error1 * Dt;
    D = (error1 - previous_error) / Dt;
    PID_value = (Kp * P) + (Ki * I) + (Kd * D);
    previous_error = error1;*/
  digitalWrite(L1, LOW);
  digitalWrite(R1, LOW);
  analogWrite(L2, mid_sp + PID_value);
  analogWrite(R2, mid_sp - PID_value);
}
