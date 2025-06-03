/*
    - VU meter (столбик громкости): от зелёного к красному
    - VU meter (столбик громкости): плавно бегущая радуга

   НАСТРОЙКА НИЖНЕГО ПОРОГА ШУМА (строки 65-71)
    - Ручная: выключаем AUTO_LOW_PASS и EEPROM_LOW_PASS, настраиваем LOW_PASS и SPEKTR_LOW_PASS вручную
    - При запуске: включаем AUTO_LOW_PASS. При подаче питания музыка должна стоять на паузе!

   Как работает алгоритм:
    - Режим громкости
    - Делается 100 измерений напряжения на АЦП
    - Ищется максимальное
    - Фильтруется по нижнему порогу шумов
    - Возводится в степень для большей "резкости" анимации
    - Фильтруется "бегущим средним"
    - Ищется "средняя" громкость за несколько секунд (тоже бегущее среднее, но очень медленное)
    - Ищем "максимальную громкость шкалы", как среднюю * некоторый коэффициент
    - Преобразуем сигнал в количество горящих светодиодов
    - Включаются светодиоды согласно режиму отрисовки
*/

// --------------------------- НАСТРОЙКИ ---------------------------
// лента
#define NUM_LEDS 146        // количество светодиодов
#define BRIGHTNESS 50     // яркость (0 - 255)

// пины
#define SOUND A0         // аналоговый пин вход аудио
#define LED_PIN 3         // пин DI светодиодной ленты

// настройки радуги
#define RAINBOW_SPEED 6    // скорость движения радуги (чем меньше число, тем быстрее радуга)
#define RAINBOW_STEP 6     // шаг изменения цвета радуги

// отрисовка
#define MODE 0              // режим при запуске
#define MAIN_LOOP 5         // период основного цикла отрисовки (по умолчанию 5)
#define SMOOTH 0.5          // коэффициент плавности анимации VU (по умолчанию 0.5)
#define MAX_COEF 1.8        // коэффициент громкости (максимальное равно срднему * этот коэф) (по умолчанию 1.8)
#define LOW_PASS 2          // нижний порог шумов

// сигнал
#define EXP 1.4             // степень усиления сигнала (для более "резкой" работы) (по умолчанию 1.4)
// --------------------------- НАСТРОЙКИ ---------------------------

// --------------------- ДЛЯ РАЗРАБОТЧИКОВ ---------------------
// цвета
#define BLUE     0x0000FF
#define RED      0xFF0000
#define GREEN    0x00ff00
#define CYAN     0x00FFFF
#define MAGENTA  0xFF00FF
#define YELLOW   0xFFFF00
#define WHITE    0xFFFFFF
#define BLACK    0x000000

#include <FastLED.h>
#include <VolAnalyzer.h>

CRGB leds[NUM_LEDS];
VolAnalyzer analyzer(SOUND);  // микрофон на А0

// градиент-палитра от зелёного к красному
DEFINE_GRADIENT_PALETTE(soundlevel_gp) {
  0,    0,    255,  0,  // green
  100,  255,  255,  0,  // yellow
  150,  255,  100,  0,  // orange
  200,  255,  50,   0,  // red
  255,  255,  0,    0   // red
};
CRGBPalette32 myPal = soundlevel_gp;

//int flag;
//int counter;
byte lenght;
float soundLevel;
float soundLevel_f;
float soundLevel_old;
int currentLevel;

//int max_vol;
float averageLevel = 50;
int maxLevel = 100;
byte MAX_CH = (NUM_LEDS - 38) / 2 + 38;
int hue;
unsigned long main_timer, hue_timer;
float averK = 0.006, k = SMOOTH;
byte count;
float index = (float)255 / MAX_CH;   // коэффициент перевода для палитры
byte this_mode = MODE;
// --------------------- ДЛЯ РАЗРАБОТЧИКОВ ---------------------

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  analogReference(INTERNAL);
}

void loop() {
  /*if (flag == 0) {
      soundLevel_old = soundLevel;
      if (analyzer.tick()) {
        soundLevel = analyzer.getVol();
        //
      }
      if (soundLevel_old <= LOW_PASS && (soundLevel == 62 || soundLevel == 37)) {
        soundLevel = soundLevel_old;
        flag = 1;
      }
      }
      Serial.println(soundLevel);
      if (flag == 1) {
      counter++;
      delay(1);
      if (counter >= 500) {
        counter = 0;
        flag = 0;
      }
      }*/

  if (millis() - hue_timer > RAINBOW_SPEED) {
    if (++hue >= 255) hue = 0;
    hue_timer = millis();

  }

  if (analyzer.tick()) {
    soundLevel = analyzer.getVol();
  }
  Serial.println(soundLevel);

  // фильтр
  soundLevel_f = soundLevel * k + soundLevel_f * (1 - k);
  // если значение выше порога - начинаем самое интересное
  //if (flag == 0) {
  if (soundLevel_f > 15) {

    // расчёт общей средней громкости с обоих каналов, фильтрация.
    // Фильтр очень медленный, сделано специально для автогромкости
    averageLevel = (float)(soundLevel_f * 2) / 2 * averK + averageLevel * (1 - averK);

    // принимаем максимальную громкость шкалы как среднюю, умноженную на некоторый коэффициент MAX_COEF
    maxLevel = (float)averageLevel * MAX_COEF;

    // преобразуем сигнал в длину ленты (где MAX_CH это половина количества светодиодов)
    lenght = map(soundLevel_f, 0, maxLevel, 0, MAX_CH);

    // ограничиваем до макс. числа светодиодов
    //lenght = constrain(lenght, 0, MAX_CH);

    animation();       // отрисовать
  }
  FastLED.show();           // отправить значения на ленту
  //}
  FastLED.clear();          // очистить массив пикселей
}

void animation() {
  // согласно режиму
  switch (this_mode) {
    case 0:
      count = 0;
      for (int i = (MAX_CH - 1); i > ((MAX_CH - 1) - lenght); i--) {
        leds[i] = ColorFromPalette(myPal, (count * index));   // заливка по палитре " от зелёного к красному"
        count++;
      }
      count = 0;
      for (int i = (MAX_CH); i < (MAX_CH + lenght); i++ ) {
        leds[i] = ColorFromPalette(myPal, (count * index));   // заливка по палитре " от зелёного к красному"
        count++;
      }
      break;
    case 1:
      count = 0;
      for (int i = (MAX_CH - 1); i > ((MAX_CH - 1) - lenght); i--) {
        leds[i] = ColorFromPalette(RainbowColors_p, (count * index) / 2 - hue);  // заливка по палитре радуга
        count++;
      }
      count = 0;
      for (int i = (MAX_CH); i < (MAX_CH + lenght); i++ ) {
        leds[i] = ColorFromPalette(RainbowColors_p, (count * index) / 2 - hue);  // заливка по палитре радуга
        count++;
      }
      break;
  }
}
