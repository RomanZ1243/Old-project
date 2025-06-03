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
int k1;
int d1 = 24;
int d2 = 25;
int black = 975;
int mid_sp = 130;
int max_sp = 125;
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
    if (digitalRead(DL) == 1 && analogRead(D1) < black && analogRead(D2) < black && analogRead(D3) < black && analogRead(D4) < black && analogRead(D5) < black && analogRead(D6) < black && analogRead(D7) < black && analogRead(D8) < black) {
      k = -5;
      flag = 1;
    }
    if (digitalRead(DR) == 1 && analogRead(D1) < black && analogRead(D2) < black && analogRead(D3) < black && analogRead(D4) < black && analogRead(D5) < black && analogRead(D6) < black && analogRead(D7) < black && analogRead(D8) < black) {
      k = 5;
      flag = 1;
    }
    if (digitalRead(DL) == 0 && digitalRead(DR) == 0) {
      if (analogRead(D8) > black) {
        i++;
      }
      if (analogRead(D7) > black) {
        i++;
      }
      if (analogRead(D6) > black) {
        i++;
      }
      if (analogRead(D5) > black) {
        i++;
      }
      if (analogRead(D4) > black) {
        i++;
      }
      if (analogRead(D3) > black) {
        i++;
      }
      if (analogRead(D2) > black) {
        i++;
      }
      if (analogRead(D1) > black) {
        i++;
      }
      //Serial.println(i);
      if (i >= 6) {
        //Serial.println(i);
        flag = 2;
      }
      i = 0;
    }
    digitalWrite(L1, LOW);
    digitalWrite(R1, LOW);
    analogWrite(L2, mid_sp + (k * d1));
    analogWrite(R2, mid_sp - (k * d1));
  }

  if (flag == 1) {
    Serial.println("1");
    if (analogRead(D8) > black) {
      k1 = -4;
    }
    if (analogRead(D1) > black) {
      k1 = 4;
    }
    if (analogRead(D8) > black && analogRead(D7) > black) {
      k1 = -3;
    }
    if (analogRead(D7) > black && analogRead(D6) > black) {
      k1 = -2;
    }
    if (analogRead(D6) > black && analogRead(D5) > black) {
      k1 = -1;
    }

    if (analogRead(D5) > black && analogRead(D4) > black) {
      k1 = 0;
    }

    if (analogRead(D4) > black && analogRead(D3) > black) {
      k1 = 1;
    }
    if (analogRead(D3) > black && analogRead(D2) > black) {
      k1 = 2;
    }
    if (analogRead(D2) > black && analogRead(D1) > black) {
      k1 = 3;
    }
    if (digitalRead(DL) == 1) {
      k1 = -5;
    }
    if (digitalRead(DR) == 1) {
      k1 = 5;
    }
    if (k == -5) {
      analogWrite(L1, 250);//
      analogWrite(L2, 250);
      analogWrite(R1, LOW);
      analogWrite(R2, mid_sp - (k1 * d1));
      if (analogRead(D5) > black) {
        flag = 0;
      }
    }
    if (k == 5) {
      analogWrite(L1, LOW);
      analogWrite(L2, mid_sp + (k1 * d1));
      analogWrite(R1, 250);//
      analogWrite(R2, 250);
      if (analogRead(D4) > black) {
        flag = 0;
      }
    }
  }
  if (flag == 2) {
    analogWrite(L1, LOW);
    analogWrite(L2, mid_sp);
    analogWrite(R1, LOW);
    analogWrite(R2, mid_sp);
    delay(100);
    flag = 0;
  }
}
