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
byte* registerState;
//int var;

long effectId = 0;
long prevEffect = 0;
long effectRepeat = 0;
long effectSpeed = 30;

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
  Serial.println(9600);
}

void loop() {
  for (int i = 0; i <= 4; i++) {
    switch (i) {
      case 1:
        digitalWrite(l1, LOW);
        digitalWrite(l2, HIGH);
        digitalWrite(l3, HIGH);
        digitalWrite(l4, HIGH);
        regWrite(0, 1);
        regWrite(1, 1);
        regWrite(2, 1);
        regWrite(3, 1);
        regWrite(4, 1);
        regWrite(5, 1);
        regWrite(6, 1);
        regWrite(7, 1);
        regWrite(8, 1);
        regWrite(9, 1);
        regWrite(10, 1);
        regWrite(11, 1);
        regWrite(12, 1);
        regWrite(13, 1);
        regWrite(14, 1);
        regWrite(15, 1);
        break;
      case 2:
        digitalWrite(l1, HIGH);
        digitalWrite(l2, LOW);
        digitalWrite(l3, HIGH);
        digitalWrite(l4, HIGH);
        regWrite(0, 1);
        regWrite(1, 1);
        regWrite(2, 1);
        regWrite(3, 1);
        regWrite(4, 1);
        regWrite(5, 1);
        regWrite(6, 1);
        regWrite(7, 1);
        regWrite(8, 1);
        regWrite(9, 1);
        regWrite(10, 1);
        regWrite(11, 1);
        regWrite(12, 1);
        regWrite(13, 1);
        regWrite(14, 1);
        regWrite(15, 1);
        break;
      case 3:
        digitalWrite(l1, HIGH);
        digitalWrite(l2, HIGH);
        digitalWrite(l3, LOW);
        digitalWrite(l4, HIGH);
        regWrite(0, 1);
        regWrite(1, 1);
        regWrite(2, 1);
        regWrite(3, 1);
        regWrite(4, 1);
        regWrite(5, 1);
        regWrite(6, 1);
        regWrite(7, 1);
        regWrite(8, 1);
        regWrite(9, 1);
        regWrite(10, 1);
        regWrite(11, 1);
        regWrite(12, 1);
        regWrite(13, 1);
        regWrite(14, 1);
        regWrite(15, 1);
        break;
      case 4:
        digitalWrite(l1, HIGH);
        digitalWrite(l2, HIGH);
        digitalWrite(l3, HIGH);
        digitalWrite(l4, LOW);
        regWrite(0, 1);
        regWrite(1, 1);
        regWrite(2, 1);
        regWrite(3, 1);
        regWrite(4, 1);
        regWrite(5, 1);
        regWrite(6, 1);
        regWrite(7, 1);
        regWrite(8, 1);
        regWrite(9, 1);
        regWrite(10, 1);
        regWrite(11, 1);
        regWrite(12, 1);
        regWrite(13, 1);
        regWrite(14, 1);
        regWrite(15, 1);
        break;
      case 5:
        digitalWrite(l1, HIGH);
        digitalWrite(l2, HIGH);
        digitalWrite(l3, HIGH);
        digitalWrite(l4, HIGH);
        regWrite(0, 1);
        regWrite(1, 1);
        regWrite(2, 1);
        regWrite(3, 1);
        regWrite(4, 1);
        regWrite(5, 1);
        regWrite(6, 1);
        regWrite(7, 1);
        regWrite(8, 1);
        regWrite(9, 1);
        regWrite(10, 1);
        regWrite(11, 1);
        regWrite(12, 1);
        regWrite(13, 1);
        regWrite(14, 1);
        regWrite(15, 1);
        break;
    }
    if (i == 4) {
      i = 0;
    }
    delay(500);
  }
  /*digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(l3, LOW);
    digitalWrite(l4, LOW);
    regWrite(0, 1);
    regWrite(1, 1);
    regWrite(2, 1);
    regWrite(3, 1);
    regWrite(4, 1);
    regWrite(5, 1);
    regWrite(6, 1);
    regWrite(7, 1);
    regWrite(8, 1);
    regWrite(9, 1);
    regWrite(10, 1);
    regWrite(11, 1);
    regWrite(12, 1);
    regWrite(13, 1);
    regWrite(14, 1);
    regWrite(15, 1);*/
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
