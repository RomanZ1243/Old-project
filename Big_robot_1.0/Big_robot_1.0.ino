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


#include <VolAnalyzer.h>
VolAnalyzer analyzer(A0);  // микрофон на А0
// --------------------------- НАСТРОЙКИ ---------------------------
// лента
#define NUM_LEDS 92        // количество светодиодов
#define BRIGHTNESS 50     // яркость (0 - 255)

// пины
#define SOUND A0         // аналоговый пин вход аудио
#define LED_PIN 7         // пин DI светодиодной ленты

// настройки радуги
#define RAINBOW_SPEED 6    // скорость движения радуги (чем меньше число, тем быстрее радуга)
#define RAINBOW_STEP 6     // шаг изменения цвета радуги

// отрисовка
#define MODE 0              // режим при запуске
#define MAIN_LOOP 5         // период основного цикла отрисовки (по умолчанию 5)
#define SMOOTH 0.5          // коэффициент плавности анимации VU (по умолчанию 0.5)
#define MAX_COEF 1.8        // коэффициент громкости (максимальное равно срднему * этот коэф) (по умолчанию 1.8)

// сигнал
#define EXP 1.4             // степень усиления сигнала (для более "резкой" работы) (по умолчанию 1.4)

// нижний порог шумов
int LOW_PASS = 2;         // нижний порог шумов режим VU, ручная настройка
//int SPEKTR_LOW_PASS = 40;   // нижний порог шумов режим спектра, ручная настройка
//#define AUTO_LOW_PASS 0     // разрешить настройку нижнего порога шумов при запуске (по умолч. 0)
//#define EEPROM_LOW_PASS 1   // порог шумов хранится в энергонезависимой памяти (по умолч. 1)
//#define LOW_PASS_ADD 13     // "добавочная" величина к нижнему порогу, для надёжности (режим VU)
// --------------------------- НАСТРОЙКИ ---------------------------

/*
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

#define STRIPE NUM_LEDS / 5

//#define FHT_N 64         // ширина спектра х2
//#define LOG_OUT 1
#include <FastLED.h>

//#include <EEPROMex.h>

CRGB leds[NUM_LEDS];

// градиент-палитра от зелёного к красному
DEFINE_GRADIENT_PALETTE(soundlevel_gp) {
  0,    0,    255,  0,  // green
  100,  255,  255,  0,  // yellow
  150,  255,  100,  0,  // orange
  200,  255,  50,   0,  // red
  255,  255,  0,    0   // red
};
CRGBPalette32 myPal = soundlevel_gp;

int puls;
int flag;
int counter;
byte lenght;
float soundLevel;
float soundLevel_f;
float soundLevel_old;
int currentLevel;

int max_vol;
float averageLevel = 50;
int maxLevel = 100;
byte MAX_CH = NUM_LEDS / 2;
int hue;
unsigned long main_timer, hue_timer;
float averK = 0.006, k = SMOOTH;
byte count;
float index = (float)255 / MAX_CH;   // коэффициент перевода для палитры
byte this_mode = MODE;

/*#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
  #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))*/
// --------------------- ДЛЯ РАЗРАБОТЧИКОВ ---------------------

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  // для увеличения точности уменьшаем опорное напряжение,
  // выставив EXTERNAL и подключив Aref к выходу 3.3V на плате через делитель
  // GND ---[10-20 кОм] --- REF --- [10 кОм] --- 3V3
  // в данной схеме GND берётся из А0 для удобства подключения
  analogReference(INTERNAL);
  analyzer.setPulseMax(100);
  analyzer.setPulseMin(35);
  analyzer.setPulseTimeout(500);
  // жуткая магия, меняем частоту оцифровки до 18 кГц
  // команды на ебучем ассемблере, даже не спрашивайте, как это работает
  /*sbi(ADCSRA, ADPS2);
    cbi(ADCSRA, ADPS1);
    sbi(ADCSRA, ADPS0);*/

  /*if (AUTO_LOW_PASS && !EEPROM_LOW_PASS) {         // если разрешена автонастройка нижнего порога шумов
    autoLowPass();
    }
    if (EEPROM_LOW_PASS) {                // восстановить значения шумов из памяти
    LOW_PASS = EEPROM.readInt(0);
    SPEKTR_LOW_PASS = EEPROM.readInt(2);
    }*/
}

void loop() {
  if (analyzer.tick()) {
    soundLevel = analyzer.getVol();
  }
  /*if (analyzer.tick()) {
    soundLevel = analyzer.getRaw();
    if(soundLevel > max_vol){
      max_vol = soundLevel;
    }
    puls = analyzer.pulse();
    //Serial.println(soundLevel);
    }*/
  //Serial.println(max_vol);
  //if (puls == 0) {

  //Serial.println(analyzer.pulse());
  /*if (flag == 0) {
    soundLevel_old = soundLevel;
    if (analyzer.tick()) {
      soundLevel = analyzer.getVol();
      //
    }
    if (soundLevel_old <= LOW_PASS && soundLevel >= 60 && soundLevel <= 65) {
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
  // кольцевое изменение положения радуги по таймеру
  if (millis() - hue_timer > RAINBOW_SPEED) {
    if (++hue >= 255) hue = 0;
    hue_timer = millis();

  }

  // главный цикл отрисовки
  //if (millis() - main_timer > MAIN_LOOP) {
  // сбрасываем значения
  //soundLevel = 0;
  /*for (byte i = 0; i < 100; i ++) {                                 // делаем 100 измерений
    currentLevel = analogRead(SOUND);
    if (soundLevel < currentLevel) soundLevel = currentLevel;       // ищем максимальное
    }

    // фильтруем по нижнему порогу шумов
    soundLevel = map(soundLevel, LOW_PASS, 1023, 0, 500);

    // ограничиваем диапазон
    soundLevel = constrain(soundLevel, 0, 500);

    // возводим в степень (для большей чёткости работы)*/
  //soundLevel = pow(soundLevel, EXP);

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
    lenght = constrain(lenght, 0, MAX_CH);

    animation();       // отрисовать
  }
  //main_timer = millis();    // сбросить таймер
  //}
  /*if (soundLevel == 0) {
    flag = 0;
    }*/
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

/*void autoLowPass() {
  // для режима VU
  delay(10);                                // ждём инициализации АЦП
  int thisMax = 0;                          // максимум
  int thisLevel;
  for (byte i = 0; i < 200; i++) {
    thisLevel = analogRead(SOUND_R);        // делаем 200 измерений
    if (thisLevel > thisMax)                // ищем максимумы
      thisMax = thisLevel;                  // запоминаем
    delay(4);                               // ждём 4мс
  }
  LOW_PASS = thisMax + LOW_PASS_ADD;        // нижний порог как максимум тишины + некая величина

  // для режима спектра
  thisMax = 0;
  for (byte i = 0; i < 100; i++) {          // делаем 100 измерений
    analyzeAudio();                         // разбить в спектр
    for (byte j = 2; j < 32; j++) {         // первые 2 канала - хлам
      thisLevel = fht_log_out[j];
      if (thisLevel > thisMax)              // ищем максимумы
        thisMax = thisLevel;                // запоминаем
    }
    delay(4);                               // ждём 4мс
  }
  SPEKTR_LOW_PASS = thisMax + LOW_PASS_FREQ_ADD;  // нижний порог как максимум тишины

  if (EEPROM_LOW_PASS && !AUTO_LOW_PASS) {
    EEPROM.updateInt(0, LOW_PASS);
    EEPROM.updateInt(2, SPEKTR_LOW_PASS);
  }
  }*/

/*void analyzeAudio() {
  for (int i = 0 ; i < FHT_N ; i++) {
    int sample = analogRead(SOUND_R_FREQ);
    fht_input[i] = sample; // put real data into bins
  }
  fht_window();  // window the data for better frequency response
  fht_reorder(); // reorder the data before doing the fht
  fht_run();     // process the data in the fht
  fht_mag_log(); // take the output of the fht
  }*/
