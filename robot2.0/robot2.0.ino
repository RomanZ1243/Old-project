#define D1 A0
#define D2 A1
#define D3 A2
#define D4 A3
#define D5 A4
#define D6 A5
#define D7 A6
#define D8 A7

#define AIN1 2
#define AIN2 3
#define STBY1 4
#define BIN1 5
#define BIN2 6
#define STBY2 7
#define PWMA 9
#define PWMB 10

int a;
int k;
int d = 30;
int black = 800;
int mid_sp = 125;
int max_sp = 125;
int flag = 0;
int i;
float P;
float I;
float D;
float Kp = 22;//22
float Ki = 0.8;//0.8
float Kd = 40;//40
float Kk = 0.005;//0.005
float PID_value;
int error1;
int previous_error;


void setup() {
  pinMode(AIN1 , OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  digitalWrite(STBY1, HIGH);
  digitalWrite(STBY2, HIGH);
  //digitalWrite(PWMA, HIGH);
  //digitalWrite(PWMB, HIGH);
  /*digitalWrite(AIN1, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN2, LOW);*/
  Serial.begin(9600);
}

void loop() {
  if (flag == 0) {

    if (analogRead(D7) > black) {
      k = 3;
    }
    if (analogRead(D6) > black) {
      k = 2;
    }
    if (analogRead(D5) > black) {
      k = 1;
    }
    if (analogRead(D4) > black && analogRead(D5) > black) {
      k = 0;
    }
    if (analogRead(D4) > black) {
      k = -1;
    }
    if (analogRead(D3) > black) {
      k = -2;
    }
    if (analogRead(D2) > black) {
      k = -3;
    }
    if (analogRead(D1) > black) {
      k = -4;
      flag = 1;
    }
    if (analogRead(D8) > black) {
      k = 4;
      flag = 1;
    }

    if (analogRead(D1) > black) {
      i++;
    }
    if (analogRead(D2) > black) {
      i++;
    }
    if (analogRead(D3) > black) {
      i++;
    }
    if (analogRead(D4) > black) {
      i++;
    }
    if (analogRead(D5) > black) {
      i++;
    }
    if (analogRead(D6) > black) {
      i++;
    }
    if (analogRead(D7) > black) {
      i++;
    }
    if (analogRead(D8) > black) {
      i++;
    }
    if (i >= 5) {
      a++;
      if (a > 2) {
        flag = 2;
      }
    }
    i = 0;

    error1 = k;
    P = error1;
    I = I + error1;
    D = error1 - previous_error;
    PID_value = (Kp * P) + (Ki * I) + (Kd * D) + (Kk * pow(error1, 3));
    I = error1;
    previous_error = error1;

    if (mid_sp + PID_value > 254) {
      mid_sp = 0;
      PID_value = 254;
    }
    if (mid_sp - PID_value < 1) {
      mid_sp = 0;
      PID_value = 0;
    }

    digitalWrite(AIN1, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMA, mid_sp + PID_value);
    analogWrite(PWMB, mid_sp - PID_value);
  }

  if (flag == 1) {
    if (k == -4) {
      digitalWrite(AIN1, HIGH);//
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMA, 255);
      analogWrite(PWMB, max_sp);
      if (analogRead(D5) > black) {
        flag = 0;
      }
    }
    //Serial.println(analogRead(D5));
    if (k == 4) {
      digitalWrite(AIN1, HIGH);//
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, HIGH);
      analogWrite(PWMA, max_sp);
      analogWrite(PWMB, 255);
      if (analogRead(D4) > black) {
        flag = 0;
      }
    }
  }
  if (flag == 2) {
    //Serial.println(i);
    analogWrite(PWMA, mid_sp);
    analogWrite(PWMB, mid_sp);
    delay(100);
    flag = 0;
  }
}
