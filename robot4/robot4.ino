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

#define L1 6
#define L2 9
#define R1 11
#define R2 10

int k;
int d = 15;
int black = 975;
int max_sp = 75;
int flag;
int i;

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
  if (flag == 0) {
    Serial.println("1");
    if (analogRead(D8) > black) {
      k = -4;
    }
    if (analogRead(D1) > black) {
      k = 4;
    }
    if (analogRead(D8) > black && analogRead(D7) > black) {
      k = -3;
    }
    if (analogRead(D7) > black && analogRead(D6) > black) {
      k = -2;
    }
    if (analogRead(D6) > black && analogRead(D5) > black) {
      k = -1;
    }

    if (analogRead(D5) > black && analogRead(D4) > black) {
      k = 0;
    }

    if (analogRead(D4) > black && analogRead(D3) > black) {
      k = 1;
    }
    if (analogRead(D3) > black && analogRead(D2) > black) {
      k = 2;
    }
    if (analogRead(D2) > black && analogRead(D1) > black) {
      k = 3;
    }
    if (analogRead(D1) > black) {
      k = 4;
    }
    if (digitalRead(DL) == 1) {
      k = -5;
      analogWrite(L1, 255);
      analogWrite(L2, 255);
      analogWrite(R1, LOW);
      analogWrite(R2, max_sp);
      flag = 1;
    }
    if (digitalRead(DR) == 1) {
      k = 5;
      analogWrite(L1, LOW);
      analogWrite(L2, max_sp);
      analogWrite(R1, 255);
      analogWrite(R2, 255);
      flag = 1;
    }
    /*if (digitalRead(DL) == 0 && digitalRead(DR) == 0) {
      if (analogRead(D8) > black1) {
        i++;
      }
      if (analogRead(D7) > black2) {
        i++;
      }
      if (analogRead(D6) > black3) {
        i++;
      }
      if (analogRead(D5) > black4) {
        i++;
      }
      if (analogRead(D4) > black5) {
        i++;
      }
      if (analogRead(D3) > black6) {
        i++;
      }
      if (analogRead(D2) > black7) {
        i++;
      }
      if (analogRead(D1) > black8) {
        i++;
      }
      //Serial.println(i);
      if (i >= 4) {
        //Serial.println(i);
        //flag = 2;
      }
      i = 0;
    }*/
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
  }

  if (flag == 1) {
    if (k == -5) {
      if (analogRead(D5) > black) {
        flag = 0;
      }
    }
    if (k == 5) {
      if (analogRead(D4) > black) {
        flag = 0;
      }
    }
  }

  if (flag == 2) {
    Serial.println(i);
    analogWrite(L1, 255);
    analogWrite(L2, 255);
    analogWrite(R1, 255);
    analogWrite(R2, 255);
    delay(500);
    flag = 0;
  }
}
