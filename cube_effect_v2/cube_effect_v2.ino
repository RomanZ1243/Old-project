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
byte flag;
byte num0;
byte z;
byte num[4][16] = {};
byte a;
byte count;
byte i_count;

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
  //show_pixel();
  //delay(100000);
}

void random_pixel() {
  if (count == 64) {
    for (int i = 0; i <= 3; i++) {
      for (int i1 = 0; i1 <= 15; i1++) {
        num[i][i1] = 0;
      }
    }
  }
  if (flag == 0) {
    num0 = random(16);
    z = random(4);
    x = num[z][num0];
    if (x == 0) {
      num[z][num0] = 1;
      flag = 1;
    }
  }
  if (flag == 1) {
    //clear_cube();
    show_pixel();
    a++;
    delay(1);
    if (a == 50) {
      a = 0;
      flag = 0;
    }
  }
}

/*void pixel(byte x, byte y, byte z, boolean val) {
  layer(z);
  num = 4 * y + x;
  regWrite(num, val);
  }*/

void pixel1(byte z2, byte num6, boolean val1) {
  layer(z2);
  regWrite(num6 - 1, val1);
}

void show_pixel() {
  for (int i = 0; i <= 3; i++) {
    for (int i1 = 0; i1 <= 15; i1++) {
      layer(i);
      regWrite(i1, num[i][i1]);
    }
  }
}

void clear_cube() {
  for (int i = 0; i <= 15; i++) {
    regWrite(i, 0);
  }
}

void layer(byte l) {
  switch (l) {
    case 0:
      digitalWrite(l4, HIGH);
      digitalWrite(l1, LOW);
      break;
    case 1:
      digitalWrite(l1, HIGH);
      digitalWrite(l2, LOW);
      break;
    case 2:
      digitalWrite(l2, HIGH);
      digitalWrite(l3, LOW);
      break;
    case 3:
      digitalWrite(l3, HIGH);
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
  count++;
  i_count++;
  if (i_count == 16) {
    digitalWrite(latchPin, HIGH);
    i_count = 0;
  }
}
