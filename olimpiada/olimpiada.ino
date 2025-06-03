#define D1 A0//указываем названия датчикам
#define D2 A1
#define D3 A2
#define D4 A3
#define D5 A4
#define D6 A5
#define D7 A6
#define D8 A7

#define AIN1 2//указываем названия пинов для управления моторами
#define AIN2 3
#define STBY1 4
#define BIN1 5
#define BIN2 6
#define STBY2 7
#define PWMA 9
#define PWMB 10

#define led 13//указываем название светодиоду

int black = 800;//выставляем значение при котором даьтчики видит черный
int mid_sp = 100;//выставляем скорость моторов
int flag = 0;
int a;

void setup() {
  pinMode(AIN1 , OUTPUT);//подключаем пины для управления моторами
  pinMode(AIN2, OUTPUT);
  pinMode(STBY1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(led, OUTPUT);//подключаем светодиод
  digitalWrite(STBY1, HIGH);//включаем драйверы
  digitalWrite(STBY2, HIGH);
  randomSeed(analogRead(1));//подключаем рондомайзер
}

void loop() {
  if (flag == 0) {//основной цикл
    if (analogRead(D1) > black || analogRead(D3) > black || analogRead(D4) > black || analogRead(D5) > black || analogRead(D6) > black || analogRead(D7) > black || analogRead(D8) > black) {//если какой-то датчик увидит линию
      digitalWrite(AIN1, LOW);//едет назад
      digitalWrite(BIN1, LOW);
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN2, HIGH);
      analogWrite(PWMA, mid_sp);
      analogWrite(PWMB, mid_sp);
      delay(500);//задержка
      digitalWrite(AIN1, HIGH);//останавливается
      digitalWrite(BIN1, HIGH);
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN2, HIGH);
      analogWrite(PWMA, mid_sp);
      analogWrite(PWMB, mid_sp);
      delay(200);//задержка
      flag = 1;//переходим в цикл поворота
    }
    digitalWrite(AIN1, HIGH);//едет прямо
    digitalWrite(BIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMA, mid_sp);
    analogWrite(PWMB, mid_sp);
  }

  if (flag == 1) {//цикл поворота
    a = random(300, 2000);//генерирует случайное значение от 300 до 2000
    digitalWrite(AIN1, LOW);//поворачивает
    digitalWrite(BIN1, HIGH);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMA, mid_sp);
    analogWrite(PWMB, mid_sp);
    delay(a);//случайная задержка
    digitalWrite(AIN1, HIGH);//останавливается
    digitalWrite(BIN1, HIGH);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMA, mid_sp);
    analogWrite(PWMB, mid_sp);
    digitalWrite(led, HIGH);//включает светодиод
    delay(1000);//задержка
    digitalWrite(led, LOW);//выключает светодиод
    flag = 0;//переходим в основной цикл
  }
}
