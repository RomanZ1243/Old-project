#define BUT_U 0
#define BUT_D 0
#define BUT_L 0
#define BUT_C 0
#define BUT_R 0

byte x_pin[] = {2, 3, 4, 5, 6};
byte y_pin[] = {7, 8, 9, 10, 11, 12, 13};

boolean matrix[][7] = {
  {1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1},
};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(x_pin[i], OUTPUT);
  }
  for (int i = 0; i < 7; i++) {
    pinMode(y_pin[i], OUTPUT);
  }
  pinMode(BUT_U, INPUT_PULLUP);
  pinMode(BUT_D, INPUT_PULLUP);
  pinMode(BUT_L, INPUT_PULLUP);
  pinMode(BUT_C, INPUT_PULLUP);
  pinMode(BUT_R, INPUT_PULLUP);

  /*digitalWrite(x_pin[0], HIGH);
    digitalWrite(x_pin[1], HIGH);
    digitalWrite(x_pin[2], HIGH);
    digitalWrite(x_pin[3], HIGH);
    digitalWrite(x_pin[4], HIGH);*/
}

void loop() {
  update();
}

void x_layer(byte x1, byte en) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(x_pin[i], (x1 == i) ? en : 0);
    //Serial.println((x1 == i) ? 0 : en);
  }
}

void y_layer(byte y1, byte en) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(y_pin[i], (y1 == i) ? !en : 1);
  }
}

void update() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7; j++) {
      x_layer(i, matrix[j][i]);
      y_layer(j, matrix[j][i]);
      delay(2);
    }
  }
  /*for (int i = 0; i < 7; i++) {
    y_layer(i, 1);
    delay(300);
    }*/
}

void clear() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7; j++) {
      matrix[j][i] = 0;
    }
  }
}
