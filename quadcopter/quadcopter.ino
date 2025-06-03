#define MOTOR_FL 2
#define MOTOR_FR 3
#define MOTOR_BL 4
#define MOTOR_BR 5
#define LED_PIN 6
#define POWER A1
#define GPS_TX 31
#define GPS_RX 30
#define SHT_LOX1 44   // front
#define SHT_LOX2 45   // left
#define SHT_LOX3 46   // right
#define SHT_LOX4 47   // back
#define SHT_LOX5 43   // down

#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32
#define LOX4_ADDRESS 0x33
#define LOX5_ADDRESS 0x34

#include <RF24.h>                         // библиотека радиомодуля
#include <nRF24L01.h>                     // библиотека радиомодуля
//#include <I2Cdev.h>                       // библиотека гироскопа
#include <MPU6050_6Axis_MotionApps20.h>   // библиотека гироскопа
#include <QMC5883LCompass.h>              // библиотека компаса
#include <Adafruit_BMP280.h>              // библиотека барометра
#include <Adafruit_VL53L0X.h>             // библиотека лазерных дальномеров

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();   // front
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();   // left
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();   // right
Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();   // back
Adafruit_VL53L0X lox5 = Adafruit_VL53L0X();   // down

VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;
VL53L0X_RangingMeasurementData_t measure4;
VL53L0X_RangingMeasurementData_t measure5;

MPU6050 mpu;
RF24 radio(7, 53);
QMC5883LCompass compass;
Adafruit_BMP280 bmp;

// ЛАЗЕРНЫЕ ДАЛЬНОМЕРЫ
int lox_front;
int lox_left;
int lox_right;
int lox_back;
int lox_down;

// БАРОМЕТР
float bmp_temp;
unsigned int bmp_pres;
int bmp_alt;

// КОМПАС
int compass_x;
int compass_y;
int compass_z;
int compass_az;

// ГИРОСКОП
float gx;
float gy;
float gz;

volatile bool mpuFlag = false;  // флаг прерывания готовности
uint8_t fifoBuffer[45];         // буфер
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

const uint8_t num_channels = 128;
uint8_t values[num_channels];
byte recieved_data[3];
int transmit_data[10];  // массив, хранящий передаваемые данные

void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  digitalWrite(SHT_LOX4, HIGH);
  digitalWrite(SHT_LOX5, HIGH);
  delay(10);

  // activating LOX1 and resetting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);

  // initing LOX1
  if (!lox1.begin(LOX1_ADDRESS)) {
    while (1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
  if (!lox2.begin(LOX2_ADDRESS)) {
    while (1);
  }
  delay(10);

  // activating LOX3
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  //initing LOX3
  if (!lox3.begin(LOX3_ADDRESS)) {
    while (1);
  }
  delay(10);

  // activating LOX4
  digitalWrite(SHT_LOX4, HIGH);
  delay(10);

  //initing LOX4
  if (!lox4.begin(LOX4_ADDRESS)) {
    while (1);
  }
  delay(10);

  // activating LOX5
  digitalWrite(SHT_LOX5, HIGH);
  delay(10);

  //initing LOX5
  if (!lox5.begin(LOX5_ADDRESS)) {
    while (1);
  }
}

void read_lox() {      // считываем данные с лазерных дальномеров
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  lox3.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!
  lox4.rangingTest(&measure4, false); // pass in 'true' to get debug data printout!
  lox5.rangingTest(&measure5, false); // pass in 'true' to get debug data printout!

  if (measure1.RangeStatus != 4) {    // if not out of range
    lox_front = measure1.RangeMilliMeter;
  } else {
    lox_front = 0;
  }

  if (measure2.RangeStatus != 4) {    // if not out of range
    lox_left = measure2.RangeMilliMeter;
  } else {
    lox_left = 0;
  }

  if (measure3.RangeStatus != 4) {    // if not out of range
    lox_right = measure3.RangeMilliMeter;
  } else {
    lox_right = 0;
  }

  if (measure4.RangeStatus != 4) {    // if not out of range
    lox_back = measure4.RangeMilliMeter;
  } else {
    lox_back = 0;
  }

  if (measure5.RangeStatus != 4) {    // if not out of range
    lox_down = measure5.RangeMilliMeter;
  } else {
    lox_down = 0;
  }
}

void read_bmp() {
  bmp_temp = bmp.readTemperature();
  bmp_pres = bmp.readPressure();
  bmp_alt = bmp.readAltitude(1013.25);
}

void read_copmass() {
  compass.read();
  compass_x = compass.getX();
  compass_y = compass.getY();
  compass_z = compass.getZ();
  compass_az = compass.getAzimuth();
}

void read_mpu() {
  if (mpuFlag && mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
    // переменные для расчёта (ypr можно вынести в глобал)
    Quaternion q;
    VectorFloat gravity;
    float ypr[3];
    // расчёты
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    mpuFlag = false;
    // выводим результат в радианах (-3.14, 3.14)
    gx = degrees(ypr[2]);
    gy = degrees(ypr[1]);
    gz = degrees(ypr[0]);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  pinMode(SHT_LOX4, OUTPUT);
  pinMode(SHT_LOX5, OUTPUT);

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);
  setID();

  bmp.begin();
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);

  compass.init();
  compass.setCalibrationOffsets(115.00, -721.00, -128.00);
  compass.setCalibrationScales(1.09, 0.92, 0.97);

  mpu.initialize();
  mpu.dmpInitialize();
  mpu.setDMPEnabled(true);
  mpu.setXAccelOffset(2698);
  mpu.setYAccelOffset(-3927);
  mpu.setZAccelOffset(1083);
  mpu.setXGyroOffset(-15);
  mpu.setYGyroOffset(48);
  mpu.setZGyroOffset(27);
  attachInterrupt(2, dmpReady, RISING);

  radio.begin();              // активировать модуль
  radio.setAutoAck(1);        // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();   // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);   // размер пакета, в байтах

  radio.openReadingPipe(1, address[0]);   // хотим слушать трубу 0
  radio.setChannel(0x60);             // выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX);   // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_1MBPS); // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp();        // начать работу
  radio.startListening(); // начинаем слушать эфир, мы приёмный модуль
}

void dmpReady() {
  mpuFlag = true;
}

void loop() {
  /*read_lox();
    read_bmp();
    read_copmass();
    read_mpu();
    Serial.print(lox_front);
    Serial.print(" ");
    Serial.print(lox_right);
    Serial.print(" ");
    Serial.print(lox_back);
    Serial.print(" ");
    Serial.print(lox_left);
    Serial.print(" ");
    Serial.print(lox_down);
    Serial.print(" : ");

    Serial.print(bmp_temp);
    Serial.print(" ");
    Serial.print(bmp_pres);
    Serial.print(" ");
    Serial.print(bmp_alt);
    Serial.print(" : ");

    Serial.print(compass_x);
    Serial.print(" ");
    Serial.print(compass_y);
    Serial.print(" ");
    Serial.print(compass_z);
    Serial.print(" ");
    Serial.print(compass_az);
    Serial.print(" : ");

    Serial.print(gx);
    Serial.print(" ");
    Serial.print(gy);
    Serial.print(" ");
    Serial.print(gz);
    Serial.println();*/
  recieve_signal();
  delay(2);
  send_signal();
  delay(2);
}

void recieve_signal() {
  radio.openReadingPipe(1, address[0]);   // хотим слушать трубу 0
  byte pipeNo;
  //radio.powerUp();
  radio.startListening();
  while ( radio.available(&pipeNo)) { // есть входящие данные
    radio.read(&recieved_data, sizeof(recieved_data));
    analogWrite(13, recieved_data[0]);
    //Serial.println(recieved_data[0]);
  }
}

void send_signal() {
  radio.openWritingPipe(address[1]);  // мы - труба 0, открываем канал для передачи данных
  //read_lox();
  transmit_data[0] = lox_front;  // массив, хранящий передаваемые данные
  transmit_data[2] = lox_left;  // массив, хранящий передаваемые данные
  transmit_data[4] = lox_right;  // массив, хранящий передаваемые данные
  transmit_data[6] = lox_back;  // массив, хранящий передаваемые данные
  transmit_data[8] = lox_down;  // массив, хранящий передаваемые данные
  Serial.println(transmit_data[0]);
  radio.stopListening();
  //radio.powerUp();    // включить передатчик
  radio.write(&transmit_data, sizeof(transmit_data)); // отправить по радио
  //radio.powerDown();  // выключить передатчик

}
