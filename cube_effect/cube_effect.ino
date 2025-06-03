#define l1 2
#define l2 3
#define l3 4
#define l4 5

#define but1 6
#define but2 7

#define latchPin 8
#define dataPin 11
#define clockPin 12

#define numOfRegisters 2

byte x;
byte* registerState;
byte num;
byte count;
byte flag;
byte num0;
byte z1;
byte zz;
int num1[] = {0};
byte num2[] = {0};
byte num3[] = {0};
byte num4[] = {0};
int num5[] = {0, 0, 0, 0};
/*byte num1[] = {1, 2, 3, 4};
  byte num2[] = {5, 6, 7, 8};
  byte num3[] = {9, 10, 11, 12};
  byte num4[] = {13, 14, 15, 16};
  int num5[] = {3, 3, 3, 3};*/

long effectId = 0;
long prevEffect = 0;
long effectRepeat = 0;
long effectSpeed = 30;

//byte layer;

void setup() {
  registerState = new byte[numOfRegisters];
  for (size_t i = 0; i < numOfRegisters; i++) {
    registerState[i] = 0;
  }
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(l4, OUTPUT);

  digitalWrite(l1, HIGH);
  digitalWrite(l2, HIGH);
  digitalWrite(l3, HIGH);
  digitalWrite(l4, HIGH);
  Serial.begin(9600);

  randomSeed(analogRead(0));
}

void loop() {
  random_pixel();
}

void random_pixel() {
  if (flag == 0) {
    num0 = random(1, 17);
    //z1 = random(4);
    //num0 = 1;
    z1 = 0;
    x = num5[z1];
    flag = 1;
  }
  if (flag == 1) {
    if (z1 == 0) {
      for (int i = 0; i <= x; i++) {
        /*if (num1[i] == num0) {
          flag = 0;
          //Serial.println(num0);
          break;
        }*/
        if (i >= x && flag != 0) {
          num1[x] = num0;
          num5[z1] = num5[z1] + 1;
          Serial.println(sizeof(num1) / sizeof(num1[0]));
          //Serial.println("YES");
          flag = 2;
          break;
        }
      }
    }
    if (z1 == 1) {
      for (int i = 0; i <= x; i++) {
        if (num2[i] == num0) {
          flag = 0;
          break;
        }
        if (i >= x && flag != 0) {
          num2[x] = num0;
          num5[z1] = num5[z1] + 1;
          flag = 2;
          break;
        }
      }
    }
    if (z1 == 2) {
      for (int i = 0; i <= x; i++) {
        if (num3[i] == num0) {
          flag = 0;
          break;
        }
        if (i >= x && flag != 0) {
          num3[x] = num0;
          num5[z1] = num5[z1] + 1;
          flag = 2;
          break;
        }
      }
    }
    if (z1 == 3) {
      for (int i = 0; i <= x; i++) {
        if (num4[i] == num0) {
          flag = 0;
          break;
        }
        if (i >= x && flag != 0) {
          num4[x] = num0;
          num5[z1] = num5[z1] + 1;
          flag = 2;
          break;
        }
      }
    }
  }
  if (flag == 2) {
    //pixel1(z1 + 1, num0, 1);
    clear_cube();
    show_pixel();
    /*Serial.print(z1);
      Serial.print(" ");
      Serial.print(num0);
      Serial.print(" ");
      Serial.print(num5[0]);
      Serial.print(" ");
      Serial.print(num5[1]);
      Serial.print(" ");
      Serial.print(num5[2]);
      Serial.print(" ");
      Serial.println(num5[3]);*/

    delay(500);
    flag = 0;
  }
}

void pixel(byte x, byte y, byte z, boolean val) {
  layer(z);
  num = 4 * y + x;
  regWrite(num, val);
}

void pixel1(byte z2, byte num6, boolean val1) {
  layer(z2);
  regWrite(num6 - 1, val1);
}

void show_pixel() {
  for (int i = 0; i <= 4; i++) {
    if (i == 0) {
      for (int i1 = 0; i1 <= num5[3]; i1++) {
        regWrite(num4[i1] - 1, 0);
      }
      layer(i + 1);
      for (int i2 = 0; i2 <= num5[0]; i2++) {
        regWrite(num1[i2] - 1, 1);
      }
      delay(1);
    }
    if (i == 1) {
      for (int i1 = 0; i1 <= num5[3]; i1++) {
        regWrite(num1[i1] - 1, 0);
      }
      layer(i + 1);
      for (int i2 = 0; i2 <= num5[0]; i2++) {
        regWrite(num2[i2] - 1, 1);
      }
      delay(1);
    }
    if (i == 2) {
      for (int i1 = 0; i1 <= num5[3]; i1++) {
        regWrite(num2[i1] - 1, 0);
      }
      layer(i + 1);
      for (int i2 = 0; i2 <= num5[0]; i2++) {
        regWrite(num3[i2] - 1, 1);
      }
      delay(1);
    }
    if (i == 3) {
      for (int i1 = 0; i1 <= num5[3]; i1++) {
        regWrite(num3[i1] - 1, 0);
      }
      layer(i + 1);
      for (int i2 = 0; i2 <= num5[0]; i2++) {
        regWrite(num4[i2] - 1, 1);
      }
      delay(1);
    }
  }
}

void clear_cube() {
  regWrite(0, 0);
  regWrite(1, 0);
  regWrite(2, 0);
  regWrite(3, 0);
  regWrite(4, 0);
  regWrite(5, 0);
  regWrite(6, 0);
  regWrite(7, 0);
  regWrite(8, 0);
  regWrite(9, 0);
  regWrite(10, 0);
  regWrite(11, 0);
  regWrite(12, 0);
  regWrite(13, 0);
  regWrite(14, 0);
  regWrite(15, 0);
}

void layer(byte l) {
  digitalWrite(l1, HIGH);
  digitalWrite(l2, HIGH);
  digitalWrite(l3, HIGH);
  digitalWrite(l4, HIGH);
  switch (l) {
    case 1:
      digitalWrite(l1, LOW);
      break;
    case 2:
      digitalWrite(l2, LOW);
      break;
    case 3:
      digitalWrite(l3, LOW);
      break;
    case 4:
      digitalWrite(l4, LOW);
      break;
  }
}

void regWrite(int pin, bool state) {
  int reg = pin / 8;
  int actualPin = pin - (8 * reg);
  digitalWrite(latchPin, LOW);
  for (int i = 0; i < numOfRegisters; i++) {
    byte* states = &registerState[i];
    if (i == reg) {
      bitWrite(*states, actualPin, state);
    }
    shiftOut(dataPin, clockPin, MSBFIRST, *states);
  }
  digitalWrite(latchPin, HIGH);
}
