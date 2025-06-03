#define MOTOR_H1 4
#define MOTOR_E1 5
#define MOTOR_E2 6
#define MOTOR_H2 7

#define ECHO 11
#define TRIG 10

#define SENSOR_L A2
#define SENSOR_R A3

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_H1, OUTPUT);
  pinMode(MOTOR_E1, OUTPUT);
  pinMode(MOTOR_E2, OUTPUT);
  pinMode(MOTOR_H2, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(SENSOR_L, INPUT);
  pinMode(SENSOR_R, INPUT);
}

void loop() {
  int duration, cm;         // назначаем переменную "cm" и "duration" для показаний датчика
  digitalWrite(TRIG, LOW);  // изначально датчик не посылает сигнал
  delayMicroseconds(2);     // ставим задержку в 2 ммикросекунд

  digitalWrite(TRIG, HIGH); // посылаем сигнал
  delayMicroseconds(10);    // ставим задержку в 10 микросекунд
  digitalWrite(TRIG, LOW);  // выключаем сигнал

  duration = pulseIn(ECHO, HIGH);   // включаем прием сигнала

  cm = duration / 58;    // вычисляем расстояние в сантиметрах
  Serial.println(cm);
}

int sensor_distance() {
  int duration, cm;         // назначаем переменную "cm" и "duration" для показаний датчика
  digitalWrite(TRIG, LOW);  // изначально датчик не посылает сигнал
  delayMicroseconds(2);     // ставим задержку в 2 ммикросекунд

  digitalWrite(TRIG, HIGH); // посылаем сигнал
  delayMicroseconds(10);    // ставим задержку в 10 микросекунд
  digitalWrite(TRIG, LOW);  // выключаем сигнал

  duration = pulseIn(ECHO, HIGH);   // включаем прием сигнала

  cm = duration / 58;    // вычисляем расстояние в сантиметрах
  return cm;
}
