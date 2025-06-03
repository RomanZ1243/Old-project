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
int num1[16];
byte num2[16];
byte num3[16];
byte num4[16];
int num5[] = {0, 0, 0, 0};
/*byte num1[] = {1, 2, 3, 4};
  byte num2[] = {5, 6, 7, 8};
  byte num3[] = {9, 10, 11, 12};
  byte num4[] = {13, 14, 15, 16};
  int num5[] = {3, 3, 3, 3};*/
byte mode;

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
  // put your main code here, to run repeatedly:
  show_pixel();
  delay(100000);
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
    /*if (i == 1) {
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
    }*/
  }
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
