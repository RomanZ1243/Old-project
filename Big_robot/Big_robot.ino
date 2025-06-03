#define LED_DT 2            // пин DIN ленты
#define MATRIX 5            // пин подключения второй Arduino nano для управления матрицами
#define rx 4
#define tx 3

#define LED_COUNT 146       // число светодиодов в кольце ленте (146)
#define BOTTOM_INDEX 10     // светодиод начала отсчёта
#define max_bright 50       // максимальная яркость (0 - 255)

#include <FastLED.h>         // библиотека для работы с лентой
#include <SoftwareSerial.h>

struct CRGB leds[LED_COUNT];
SoftwareSerial mySerial(rx, tx);
int ledsX[LED_COUNT][3];     //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)

int numMode;
byte ledMode = 1;
byte ledModeCopy = 30;

// цвета мячиков для режима
byte ballColors[3][3] = {
  {0xff, 0, 0},
  {0xff, 0xff, 0xff},
  {0   , 0   , 0xff},
};

// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------
boolean flag;                    // приравниваем переменные в switch только один раз
byte count;
int score;                   // замена i (вместо for)
int counter = 0;             // счетчик вместо delay
int Position = 0;            // переменная для эффектов

byte thisdelay = 20;         //-FX LOOPS DELAY VAR
byte thishue = 0;            //-FX LOOPS DELAY VAR
int thissat = 255;           //-FX LOOPS DELAY VAR

int idex = 0;                //-LED INDEX (0 to LED_COUNT-1
int ihue = 0;                //-HUE (0-255)
// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------

void one_color_eyebrows(int cred, int cgrn, int cblu) {     //-SET ALL LEDS TO ONE COLOR
  for (int i2 = 0 ; i2 < BOTTOM_INDEX; i2++ ) {
    leds[i2].setRGB(cred, cgrn, cblu);
  }
}

void one_color_all(int cred, int cgrn, int cblu) {          //-SET ALL LEDS TO ONE COLOR
  for (int i = BOTTOM_INDEX ; i < LED_COUNT; i++ ) {
    leds[i].setRGB( cred, cgrn, cblu);
  }
}

void one_color_allHSV(int ahue) {                           //-SET ALL LEDS TO ONE COLOR (HSV)
  for (int i = BOTTOM_INDEX ; i < LED_COUNT; i++ ) {
    leds[i] = CHSV(ahue, thissat, 255);
  }
}

void setup() {
  //Serial.begin(9600);
  //Serial.setTimeout(100);
  pinMode(MATRIX, OUTPUT);
  mySerial.begin(9600);
  mySerial.setTimeout(100);                            // открыть порт для связи
  LEDS.setBrightness(max_bright);                      // ограничить максимальную яркость
  LEDS.addLeds<WS2811, LED_DT, GRB>(leds, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  one_color_all(0, 0, 0);                              // погасить все светодиоды на теле
  one_color_eyebrows(0, 0, 0);                         // погасить все светодиоды на голове
  LEDS.show();
  digitalWrite(MATRIX, LOW);
}

void loop() {
  change_mode(question());
}

void change_mode(int newmode) {
  //Serial.println(newmode);
  switch (newmode) {                                          //---ALL OFF
    case 1: one_color_all(0, 0, 0); LEDS.show(); break;
    case 2: one_color_all(255, 255, 255); LEDS.show(); break; //---ALL ON
    case 3: thisdelay = 20; break;                            //---rainbow_fade
    case 4: thisdelay = 5; break;                             //---new_rainbow_loop
    case 5:                                                   //---rainbowCycle
      thisdelay = 20;
      if (flag == 0) {
        counter = thisdelay;
        flag = 1;
      }
      break;
    case 6: thisdelay = 25; thishue = 0; break;               //---rgb_propeller
    case 7: thisdelay = 50; break;                           //---rule30 (RED)
    case 8: thisdelay = 0; break;                             //---sparkle
    case 9: thisdelay = 35; break;                            //---random_color_pop
    case 10: thisdelay = 25; break;                           //---line_fade
    case 11:                                                  //---runningLights
      thisdelay = 50;
      if (flag == 0) {
        counter = thisdelay;
        flag = 1;
      }
      break;
    case 12: thisdelay = 50; break;                          //---theaterChase

    case 21: one_color_all(255, 0, 0); LEDS.show(); break;   //---ALL RED
    case 22: one_color_all(0, 255, 0); LEDS.show(); break;   //---ALL GREEN
    case 23: one_color_all(0, 0, 255); LEDS.show(); break;   //---ALL BLUE
    case 24: one_color_all(255, 255, 0); LEDS.show(); break; //---ALL COLOR X
    case 25: one_color_all(0, 255, 255); LEDS.show(); break; //---ALL COLOR Y
    case 26: one_color_all(255, 0, 255); LEDS.show(); break; //---ALL COLOR Z
  }

  switch (newmode) {
    case 999: break;                                              // пазуа
    case 3: rainbow_fade(); break;                                // плавная смена цветов всей ленты
    case 4: new_rainbow_loop(); break;                            // крутая плавная вращающаяся радуга
    case 5: rainbowCycle(thisdelay); break;                       // очень плавная вращающаяся радуга (круг)
    case 6: rgb_propeller(); break;                               // RGB пропеллер
    case 7: rule30(); break;                                      // безумие красных светодиодов
    case 8: Sparkle(0xff, 0xff, 0xff, thisdelay); break;          // случайные вспышки белого цвета
    case 9: random_color_pop(); break;                            // безумие случайных вспышек
    case 10: line_fade(170, 20, 2, thisdelay); break;                        // бегущие линии (цвет, количество светодиодов в линии, количество линий)
    case 11: RunningLights(0x82, 0x00, 0xff, thisdelay); break;   // бегущие огни
    case 12: theaterChase(0xff, 0, 0, thisdelay); break;          // бегущие каждые 3 (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ НЕЧЁТНОЕ)
  }
}

void change_mode_eyebrows(int newmode1) {
  switch (newmode1) {
    case 30: one_color_eyebrows(0, 0, 0); break;
    case 31: one_color_eyebrows(255, 255, 255); break;
    case 32: one_color_eyebrows(255, 0, 0); break;
    case 33: one_color_eyebrows(0, 255, 0); break;
    case 34: one_color_eyebrows(0, 0, 255); break;
  }
}

int question() {
  if (mySerial.available() > 0) {     // если что-то прислали
    numMode = mySerial.parseInt();    // парсим в тип данных int
    mySerial.println(numMode);
    if (numMode == 40) {
      digitalWrite(MATRIX, HIGH);
    }
    else if (numMode == 41) {
      digitalWrite(MATRIX, LOW);
    }
    else {
      if (numMode > 0) {
        one_color_all(0, 0, 0);

        if (numMode < 30) {
          ledMode = numMode;
        }
        else if (numMode >= 30) {
          ledModeCopy = numMode;
        }
        change_mode_eyebrows(ledModeCopy);
        score = 0;                    // обнуляем переменную (вместо for)
        counter = 0;                  // обнуляем счетчик
      }
    }
    delay(5);
  }
  return ledMode;
}

void rainbow_fade() { //3
  ihue++;
  if (ihue > 255) {
    ihue = 0;
  }
  for (int idex = BOTTOM_INDEX ; idex < LED_COUNT; idex++ ) {
    leds[idex] = CHSV(ihue, thissat, 255);
  }
  LEDS.show();
  delay(thisdelay);
}

void new_rainbow_loop() { //4
  ihue -= 1;
  fill_rainbow( leds, LED_COUNT, ihue );
  LEDS.show();
  delay(thisdelay);
}

void rainbowCycle(int SpeedDelay) { //5
  byte *c;
  uint16_t i;
  counter++;
  delay(1);
  if (counter >= SpeedDelay) {
    counter = 0;
    for (i = BOTTOM_INDEX; i < LED_COUNT; i++) {
      c = Wheel(((i * 256 / (LED_COUNT - BOTTOM_INDEX)) + score) & 255);
      setPixel(i, *c, *(c + 1), *(c + 2));
    }
    score++;
    FastLED.show();
  }
  if (score >= 255) {
    score = 0;
  }
}

void rgb_propeller() { //6
  idex++;
  int ghue = (thishue + 80) % 255;
  int bhue = (thishue + 160) % 255;
  int N3  = int((LED_COUNT - BOTTOM_INDEX) / 3);
  int N6  = int((LED_COUNT - BOTTOM_INDEX) / 6);
  int N12 = int((LED_COUNT - BOTTOM_INDEX) / 12);
  for (int i = 0; i < N3; i++ ) {
    int j0 = (idex + i + (LED_COUNT - BOTTOM_INDEX) - N12) % (LED_COUNT - BOTTOM_INDEX);
    int j1 = (j0 + N3) % (LED_COUNT - BOTTOM_INDEX);
    int j2 = (j1 + N3) % (LED_COUNT - BOTTOM_INDEX);
    leds[j0 + BOTTOM_INDEX] = CHSV(thishue, thissat, 255);
    leds[j1 + BOTTOM_INDEX] = CHSV(ghue, thissat, 255);
    leds[j2 + BOTTOM_INDEX] = CHSV(bhue, thissat, 255);
  }
  LEDS.show();
  delay(thisdelay);
}

//---FOR RULE30
void random_red() {
  int temprand;
  for (int i = BOTTOM_INDEX; i < LED_COUNT; i++ ) {
    temprand = random(0, 100);
    if (temprand > 50) {
      leds[i].r = 255;
    }
    if (temprand <= 50) {
      leds[i].r = 0;
    }
    leds[i].b = 0; leds[i].g = 0;
  }
  LEDS.show();
}
void random_blue() {
  int temprand;
  for (int i = BOTTOM_INDEX; i < LED_COUNT; i++ ) {
    temprand = random(0, 100);
    if (temprand > 50) {
      leds[i].b = 255;
    }
    if (temprand <= 50) {
      leds[i].b = 0;
    }
    leds[i].r = 0; leds[i].g = 0;
  }
  LEDS.show();
}
void random_green() {
  int temprand;
  for (int i = BOTTOM_INDEX; i < LED_COUNT; i++ ) {
    temprand = random(0, 100);
    if (temprand > 50) {
      leds[i].g = 255;
    }
    if (temprand <= 50) {
      leds[i].g = 0;
    }
    leds[i].b = 0; leds[i].r = 0;
  }
  LEDS.show();
}

void rule30() { //7
  random_red();
  copy_led_array();
  int iCW;
  int iCCW;
  int y = 100;
  for (int i = BOTTOM_INDEX; i < LED_COUNT; i++) {
    iCW = adjacent_cw(i);
    iCCW = adjacent_ccw(i);
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] > y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] > y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {
      leds[i].r = 0;
    }
  }
  LEDS.show();
  delay(thisdelay);
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) { //8
  int Pixel = random(BOTTOM_INDEX, LED_COUNT);
  setPixel(Pixel, red, green, blue);
  FastLED.show();
  delay(SpeedDelay);
  setPixel(Pixel, 0, 0, 0);
}

void random_color_pop() { //9
  idex = random(BOTTOM_INDEX, LED_COUNT);
  ihue = random(0, 255);
  one_color_all(0, 0, 0);
  leds[idex] = CHSV(ihue, thissat, 255);
  LEDS.show();
  delay(thisdelay);
}

void line_fade(int col, int num_led, int num, int SpeedDelay) { //10
  int k1;     // номер первого светодиода
  int br;     // яркость светодиодов
  int n;
  counter++;
  delay(1);
  if (counter >= SpeedDelay) {
    k1 = score;
    for (int i1 = 0; i1 < num; i1++) {
      br = 255;
      for (int i = 0; i < num_led + 1; i++) {
        if (k1 - i < 10) {
          n = LED_COUNT - abs((k1 - BOTTOM_INDEX) - i);
        }
        else {
          n = k1 - i;
        }
        leds[n] = CHSV(col, 255, br);
        if (num_led <= 5) {
          br = br - 255 / num_led;
        }
        else {
          br = br - 255 / (num_led + 1);
        }
      }
      if (k1 - (LED_COUNT - BOTTOM_INDEX) / num < 10) {
        k1 = LED_COUNT - abs(k1 - ((LED_COUNT - BOTTOM_INDEX) / num + BOTTOM_INDEX));
      }
      else {
        k1 = k1 - (LED_COUNT - BOTTOM_INDEX) / num;
      }
    }
    score++;
    counter = 0;
    FastLED.show();
  }
  if (score >= LED_COUNT) {
    score = BOTTOM_INDEX;
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];

  if (WheelPos < 85) {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  } else {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay) { //11
  counter++;
  delay(1);
  if (counter >= WaveDelay) {
    counter = 0;
    for (int i = BOTTOM_INDEX; i < LED_COUNT; i++) {
      setPixel(i, ((sin(i + Position) * 127 + 128) / 255)*red,
               ((sin(i + Position) * 127 + 128) / 255)*green,
               ((sin(i + Position) * 127 + 128) / 255)*blue);
    }
    score++;
    Position++; // = 0; //Position + Rate;
    FastLED.show();
  }

  if (score >= (LED_COUNT - BOTTOM_INDEX) * 2) {
    Position = 0;
    score = 0;
  }
}

void theaterChase(byte red, byte green, byte blue, int SpeedDelay) { //12
  for (int q = 0; q < 3; q++) {
    for (int i = BOTTOM_INDEX; i < LED_COUNT; i = i + 3) {
      setPixel(i + q, red, green, blue);  //turn every third pixel on
    }
    FastLED.show();
    delay(SpeedDelay);
    for (int i = BOTTOM_INDEX; i < LED_COUNT; i = i + 3) {
      setPixel(i + q, 0, 0, 0);    //turn every third pixel off
    }
  }
}

//---FIND INDEX OF ANTIPODAL OPPOSITE LED
int adjacent_cw(int i) {
  int r;
  if (i < LED_COUNT - 1) {
    r = i + 1;
  }
  else {
    r = 0;
  }
  return r;
}

//---FIND ADJACENT INDEX COUNTER-CLOCKWISE
int adjacent_ccw(int i) {
  int r;
  if (i > 0) {
    r = i - 1;
  }
  else {
    r = LED_COUNT - 1;
  }
  return r;
}

void copy_led_array() {
  for (int i = BOTTOM_INDEX; i < LED_COUNT; i++ ) {
    ledsX[i][0] = leds[i].r;
    ledsX[i][1] = leds[i].g;
    ledsX[i][2] = leds[i].b;
  }
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < LED_COUNT; i++ ) {
    setPixel(i, red, green, blue);
  }
  FastLED.show();
}
