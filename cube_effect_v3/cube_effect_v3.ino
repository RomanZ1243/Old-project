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
byte mode;
byte flag;
byte num0;
byte z;
byte num[4][16] = {};
byte a;
byte count;
byte i_count;
boolean statys;

byte flag1;
boolean effect;

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

  pinMode(but1, INPUT_PULLUP);
  pinMode(but2, INPUT_PULLUP);

  digitalWrite(l1, HIGH);
  digitalWrite(l2, HIGH);
  digitalWrite(l3, HIGH);
  digitalWrite(l4, HIGH);
  
  Serial.begin(9600);

  randomSeed(analogRead(0));
}

void loop() {
  Serial.println(effect);
  if(flag1 == 0){
    if(digitalRead(but1) == 0){
      flag1 = 1;
      clear_cube();
      effect = !effect;
    }
  }
  if(flag1 == 1){
    if(digitalRead(but1) == 1){
      flag1 = 0;
    }
  }
  
  if(effect == 0){
    full_on();
  }
  if(effect == 1){
    strobe_pixel();
  }
  
  //show_pixel();
  //delay(100000);
}

void layer_cube() {
  if (flag == 0) {
    for (int i = 0; i <= 3; i++) {
      for (int i = 0; i <= 15; i++) {
        regWrite(i, 1);
      }
      layer(i);
    }
    a++;
    delay(1);
    if (a == 100) {
      a = 0;
      flag = 1;
    }
  }
}

void full_on() {
  for (int i = 0; i <= 15; i++) {
    regWrite(i, 1);
  }
  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(l3, LOW);
  digitalWrite(l4, LOW);
}

void strobe_pixel() {
  if (flag == 0) {
    num0 = random(16);
    z = random(4);
    num[z][num0] = 1;
    //Serial.println(0);
    flag = 1;
  }
  if (flag == 1) {
    show_pixel();
    a++;
    delay(1);
    //Serial.println(a);
    if (a == 3) {
      //Serial.println(a);
      num[z][num0] = 0;
      a = 0;
      flag = 0;
    }
  }
}

void random_pixel() {
  if (count == 0) {
    statys = 0;
  }
  if (count == 64) {
    statys = 1;
  }
  if (flag == 0) {
    num0 = random(16);
    z = random(4);
    x = num[z][num0];
    if (x == statys) {
      num[z][num0] = !statys;
      if (statys == 0) {
        count++;
      }
      if (statys == 1) {
        count--;
      }
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

void pixel(byte z2, byte num6, boolean val1) {
  layer(z2);
  regWrite(num6, val1);
}

void show_pixel() {
  for (int i = 0; i <= 3; i++) {
    for (int i1 = 0; i1 <= 15; i1++) {
      layer(i);
      regWrite(i1, num[i][i1]);
      if (i == 3) {
        digitalWrite(l4, HIGH);
      }
    }
  }
}

void clear_cube() {
  for (int i = 0; i <= 15; i++) {
    regWrite(i, 0);
  }
  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(l3, LOW);
  digitalWrite(l4, LOW);
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
  i_count++;
  if (i_count == 16) {
    digitalWrite(latchPin, HIGH);
    i_count = 0;
  }
}
