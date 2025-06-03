#define IR_L 2
#define IR_R 3
#define IR_C 8
#define right_motor_speed 5
#define left_motor_speed 6
#define right_motor_direction 4
#define left_motor_direction 7

void setup() {
  pinMode(IR_L, INPUT_PULLUP);
  pinMode(IR_R, INPUT_PULLUP);
  pinMode(IR_C, INPUT_PULLUP);
  pinMode(right_motor_speed, OUTPUT);
  pinMode(right_motor_direction, OUTPUT);
  pinMode(left_motor_speed, OUTPUT);
  pinMode(left_motor_direction, OUTPUT);
}

void loop() {
  if (digitalRead(IR_L) == 0 && digitalRead(IR_C) == 1 && digitalRead(IR_R) == 0) {
    analogWrite(left_motor_speed, 200);
    digitalWrite(left_motor_direction, HIGH);
    analogWrite(right_motor_speed, 200);
    digitalWrite(right_motor_direction, HIGH);
  }
  if (digitalRead(IR_L) == 1 && digitalRead(IR_C) == 1 && digitalRead(IR_R) == 1) {
    analogWrite(left_motor_speed, 200);
    digitalWrite(left_motor_direction, HIGH);
    analogWrite(right_motor_speed, 200);
    digitalWrite(right_motor_direction, HIGH);
  }
  if (digitalRead(IR_L) == 1 && digitalRead(IR_C) == 0 && digitalRead(IR_R) == 0) {
    analogWrite(left_motor_speed, 200);
    digitalWrite(left_motor_direction, HIGH);
    analogWrite(right_motor_speed, 0);
    digitalWrite(right_motor_direction, HIGH);
  }
  if (digitalRead(IR_L) == 0 && digitalRead(IR_C) == 0 && digitalRead(IR_R) == 1) {
    analogWrite(left_motor_speed, 0);
    digitalWrite(left_motor_direction, HIGH);
    analogWrite(right_motor_speed, 200);
    digitalWrite(right_motor_direction, HIGH);
  }
  if (digitalRead(IR_L) == 1 && digitalRead(IR_C) == 1 && digitalRead(IR_R) == 0) {
    analogWrite(left_motor_speed, 200);
    digitalWrite(left_motor_direction, HIGH);
    analogWrite(right_motor_speed, 150);
    digitalWrite(right_motor_direction, HIGH);
  }
  if (digitalRead(IR_L) == 0 && digitalRead(IR_C) == 1 && digitalRead(IR_R) == 1) {
    analogWrite(left_motor_speed, 150);
    digitalWrite(left_motor_direction, HIGH);
    analogWrite(right_motor_speed, 200);
    digitalWrite(right_motor_direction, HIGH);
  }
}
