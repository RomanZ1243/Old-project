#define LED_COUNT 92         // число светодиодов в кольце/ленте
#define LED_DT 7             // пин, куда подключен DIN ленты

#include <FastLED.h>         // библиотека для работы с лентой

int max_bright = 50;         // максимальная яркость (0 - 255)
int numMode;
int ledMode = 1;

// цвета мячиков для режима
byte ballColors[3][3] = {
  {0xff, 0, 0},
  {0xff, 0xff, 0xff},
  {0   , 0   , 0xff},
};

// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------
int BOTTOM_INDEX = 0;        // светодиод начала отсчёта
int TOP_INDEX = int(LED_COUNT / 2);
int EVENODD = LED_COUNT % 2;
struct CRGB leds[LED_COUNT];
int ledsX[LED_COUNT][3];     //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)

int thisdelay = 20;          //-FX LOOPS DELAY VAR
int thisstep = 10;           //-FX LOOPS DELAY VAR
int thishue = 0;             //-FX LOOPS DELAY VAR
int thissat = 255;           //-FX LOOPS DELAY VAR

int thisindex = 0;
int thisRED = 0;
int thisGRN = 0;
int thisBLU = 0;

int Position = 0;            // переменная для эффектов
int counter = 0;             // счетчик вместо delay
int score;                   // замена i (вместо for)
int flag;                    // приравниваем переменные в switch только один раз

int idex = 0;                //-LED INDEX (0 to LED_COUNT-1
int ihue = 0;                //-HUE (0-255)
int ibright = 0;             //-BRIGHTNESS (0-255)
int isat = 0;                //-SATURATION (0-255)
int bouncedirection = 0;     //-SWITCH FOR COLOR BOUNCE (0-1)
float tcount = 0.0;          //-INC VAR FOR SIN LOOPS
int lcount = 0;              //-ANOTHER COUNTING VAR
// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------

void one_color_all(int cred, int cgrn, int cblu) {     //-SET ALL LEDS TO ONE COLOR
  for (int i = 0 ; i < LED_COUNT; i++ ) {
    leds[i].setRGB( cred, cgrn, cblu);
  }
}

void one_color_allHSV(int ahue) {                      //-SET ALL LEDS TO ONE COLOR (HSV)
  for (int i = 0 ; i < LED_COUNT; i++ ) {
    leds[i] = CHSV(ahue, thissat, 255);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);                              // открыть порт для связи
  LEDS.setBrightness(max_bright);                      // ограничить максимальную яркость
  LEDS.addLeds<WS2811, LED_DT, GRB>(leds, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  one_color_all(0, 0, 0);                              // погасить все светодиоды
  LEDS.show();
}

void loop() {
  change_mode(question());
}

void change_mode(int newmode) {
  //Serial.println(newmode);
  switch (newmode) {
    case 1: one_color_all(0, 0, 0); LEDS.show(); break;       //---ALL OFF
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
    case 7: thisdelay = 100; break;                           //---rule30 (RED)
    case 8: thisdelay = 60; thishue = 95; break;              //---radiation (GREEN)
    case 9: thisdelay = 100; thishue = 180; break;            //---quad_bright_curve (BLUE)
    case 10: thisdelay = 0; break;                            //---sparkle
    case 11: thisdelay = 35; break;                           //---random_color_pop
    case 12:                                                  //---runningLights
      thisdelay = 50;
      if (flag == 0) {
        counter = thisdelay;
        flag = 1;
      }
      break;
    case 13: thisdelay = 50; break;                           //---theaterChase
    case 14: thisdelay = 50; break;                           //---theaterChaseRainbow

    case 101: one_color_all(255, 0, 0); LEDS.show(); break;   //---ALL RED
    case 102: one_color_all(0, 255, 0); LEDS.show(); break;   //---ALL GREEN
    case 103: one_color_all(0, 0, 255); LEDS.show(); break;   //---ALL BLUE
    case 104: one_color_all(255, 255, 0); LEDS.show(); break; //---ALL COLOR X
    case 105: one_color_all(0, 255, 255); LEDS.show(); break; //---ALL COLOR Y
    case 106: one_color_all(255, 0, 255); LEDS.show(); break; //---ALL COLOR Z
  }

  switch (newmode) {
    case 999: break;                                              // пазуа
    case 3: rainbow_fade(); break;                                // плавная смена цветов всей ленты
    case 4: new_rainbow_loop(); break;                            // крутая плавная вращающаяся радуга
    case 5: rainbowCycle(thisdelay); break;                       // очень плавная вращающаяся радуга (круг)
    case 6: rgb_propeller(); break;                               // RGB пропеллер
      case 7: rule30(); break;                                    // безумие красных светодиодов
    case 8: radiation(); break;                                   // пульсирует значок радиации
    case 9: quad_bright_curve(); break;                           // полумесяц
    case 10: Sparkle(0xff, 0xff, 0xff, thisdelay); break;         // случайные вспышки белого цвета
    case 11: random_color_pop(); break;                           // безумие случайных вспышек
    case 12: RunningLights(0xff, 0xff, 0x00, thisdelay); break;   // бегущие огни
    case 13: theaterChase(0xff, 0, 0, thisdelay); break;          // бегущие каждые 3 (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ НЕЧЁТНОЕ)
    case 14: theaterChaseRainbow(thisdelay); break;               // бегущие каждые 3 радуга (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3)
  }
}

int question() {
  if (Serial.available() > 0) {     // если что то прислали
    numMode = Serial.parseInt();    // парсим в тип данных int
    if (numMode > 0) {
      counter = 0;                  // обнуляем счетчик
      score = 0;                    // обнуляем переменную (вместо for)
      ledMode = numMode;
      bouncedirection = 0;          // обнуляем переменную для эффекта
      one_color_all(0, 0, 0);       // гасим все светодиоды на ленте
    }
  }
  return ledMode;
}

void rainbow_fade() { //3
  ihue++;
  if (ihue > 255) {
    ihue = 0;
  }
  for (int idex = 0 ; idex < LED_COUNT; idex++ ) {
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
    for (i = 0; i < LED_COUNT; i++) {
      c = Wheel(((i * 256 / LED_COUNT) + score) & 255);
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
  int N3  = int(LED_COUNT / 3);
  int N6  = int(LED_COUNT / 6);
  int N12 = int(LED_COUNT / 12);
  for (int i = 0; i < N3; i++ ) {
    int j0 = (idex + i + LED_COUNT - N12) % LED_COUNT;
    int j1 = (j0 + N3) % LED_COUNT;
    int j2 = (j1 + N3) % LED_COUNT;
    leds[j0] = CHSV(thishue, thissat, 255);
    leds[j1] = CHSV(ghue, thissat, 255);
    leds[j2] = CHSV(bhue, thissat, 255);
  }
  LEDS.show();
  delay(thisdelay);
}

//---FOR RULE30
void random_red() { 
  int temprand;
  for (int i = 0; i < LED_COUNT; i++ ) {
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
  for (int i = 0; i < LED_COUNT; i++ ) {
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
  for (int i = 0; i < LED_COUNT; i++ ) {
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
  if (bouncedirection == 0) {
    random_red();
    bouncedirection = 1;
  }
  copy_led_array();
  int iCW;
  int iCCW;
  int y = 100;
  for (int i = 0; i < LED_COUNT; i++ ) {
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

void radiation() { //8
  int N3  = int(LED_COUNT / 3);
  int N6  = int(LED_COUNT / 6);
  int N12 = int(LED_COUNT / 12);
  for (int i = 0; i < N6; i++ ) {    //-HACKY, I KNOW...
    tcount = tcount + .02;
    if (tcount > 3.14) {
      tcount = 0.0;
    }
    ibright = int(sin(tcount) * 255);
    int j0 = (i + LED_COUNT - N12) % LED_COUNT;
    int j1 = (j0 + N3) % LED_COUNT;
    int j2 = (j1 + N3) % LED_COUNT;
    leds[j0] = CHSV(thishue, thissat, ibright);
    leds[j1] = CHSV(thishue, thissat, ibright);
    leds[j2] = CHSV(thishue, thissat, ibright);
  }
  LEDS.show();
  delay(thisdelay);
}

void quad_bright_curve() { //9
  int ax;
  for (int x = 0; x < LED_COUNT; x++ ) {
    if (x <= TOP_INDEX) {
      ax = x;
    }
    else if (x > TOP_INDEX) {
      ax = LED_COUNT - x;
    }
    int a = 1; int b = 1; int c = 0;
    int iquad = -(ax * ax * a) + (ax * b) + c; //-ax2+bx+c
    int hquad = -(TOP_INDEX * TOP_INDEX * a) + (TOP_INDEX * b) + c;
    ibright = int((float(iquad) / float(hquad)) * 255);
    leds[x] = CHSV(thishue, thissat, ibright);
  }
  LEDS.show();
  delay(thisdelay);
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) { //10
  int Pixel = random(LED_COUNT);
  setPixel(Pixel, red, green, blue);
  FastLED.show();
  delay(SpeedDelay);
  setPixel(Pixel, 0, 0, 0);
}

void random_color_pop() { //11
  idex = random(0, LED_COUNT);
  ihue = random(0, 255);
  one_color_all(0, 0, 0);
  leds[idex] = CHSV(ihue, thissat, 255);
  LEDS.show();
  delay(thisdelay);
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

void RunningLights(byte red, byte green, byte blue, int WaveDelay) { //12
  counter++;
  delay(1);
  if (counter >= WaveDelay) {
    counter = 0;
    for (int i = 0; i < LED_COUNT; i++) {
      setPixel(i, ((sin(i + Position) * 127 + 128) / 255)*red,
               ((sin(i + Position) * 127 + 128) / 255)*green,
               ((sin(i + Position) * 127 + 128) / 255)*blue);
    }
    score++;
    Position++; // = 0; //Position + Rate;
    FastLED.show();
  }

  if (score >= LED_COUNT * 2) {
    Position = 0;
    score = 0;
  }
}

void theaterChase(byte red, byte green, byte blue, int SpeedDelay) { //13
  for (int q = 0; q < 3; q++) {
    for (int i = 0; i < LED_COUNT; i = i + 3) {
      setPixel(i + q, red, green, blue);  //turn every third pixel on
    }
    FastLED.show();
    delay(SpeedDelay);
    for (int i = 0; i < LED_COUNT; i = i + 3) {
      setPixel(i + q, 0, 0, 0);    //turn every third pixel off
    }
  }
}

void theaterChaseRainbow(int SpeedDelay) { //14
  byte *c;
  for (int q = 0; q < 3; q++) {
    for (int i = 0; i < LED_COUNT; i = i + 3) {
      c = Wheel( (i + score) % 255);
      setPixel(i + q, *c, *(c + 1), *(c + 2)); //turn every third pixel on
    }
    FastLED.show();
    delay(SpeedDelay);
    for (int i = 0; i < LED_COUNT; i = i + 3) {
      setPixel(i + q, 0, 0, 0);    //turn every third pixel off
    }
  }
  score++;
  if (score >= 256) {
    score = 0;
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
  for (int i = 0; i < LED_COUNT; i++ ) {
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
