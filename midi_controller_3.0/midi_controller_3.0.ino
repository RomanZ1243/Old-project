#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define BUT1 8
#define BUT2 9
#define BUT3 10
#define BUT4 16
#define SIG A0
#define SH A1
#define MASTER_FADE A2

#include <SPI.h>
#include <SPI_Bus.h>
#include <MIDIUSB.h>
#include <GyverOLED.h>
#include <CD74HC4067.h>

CD74HC4067 mux(S0, S1, S2, S3);
SPI_Bus reg(_24bit, SH, MSBFIRST);
GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;

int val[17];
int val_old[17];
boolean flag[24];
boolean flag1[24];
int count;
int num;
int num_old;
int num1;
int num2;
int flag2;

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
  Serial.begin(115200);
  reg.setSelectionPolicy(SPI_Bus::SELECT_BEFORE);

  oled.init();        // инициализация
  oled.clear();       // очистка
  oled.setScale(2);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() {
  buttons();
  fader();
}

void buttons() {
  static uint32_t last_input_states = 0;
  uint32_t states = reg.read32bits();
  if (states != last_input_states) {
    uint32_t changed = states ^ last_input_states;
    last_input_states = states;
    for (int i = 0; i < reg.bandwidth() * 8; ++i) {
      if ((i >= 0 && i <= 23) && (changed & 1)) {
        if (flag[i] == 1) {
          noteOn(0, 1 + i, 127);
          MidiUSB.flush();
        }
        else if (flag[i] == 0) {
          noteOff(0, 1 + i, 127);   // Channel 0, middle C, normal velocity
          MidiUSB.flush();
        }
        flag[i] = !flag[i];
      }
      changed >>= 1;
      states >>= 1;
    }
  }
}

void fader() {
  for (int i = 0; i <= 16; i++) {
    mux.channel(i); // Устанавливаем мультиплексор на канал i
    if (i <= 15) {
      val[i] = map(analogRead(SIG), 0, 1023, 0, 127);
    }
    if (i == 16) {
      val[i] = map(analogRead(MASTER_FADE), 0, 1023, 0, 127);
    }
    if (val[i] != val_old[i]) {
      controlChange(1, 30 + i, val[i]);   // Channel 0, middle C, normal velocity
      MidiUSB.flush();
      num = i;
      num1 = val[i];
      num2 = val_old[i];
      count = 0;
      flag2 = 1;
    }

    /*count++;
      if (count >= 1000) {
      display.clearDisplay();
      }*/
    //display.display();
    val_old[i] = val[i];
  }
  if (flag2 == 1) {
    oled.setCursor(0, 1);
    if ((num_old <= 7 && num > 7) | (num_old > 7 && num <= 7)) {
      
      oled.clear();
    }

    if (num <= 7) {
      if (num2 >= 100 && num1 < 100) {
        oled.rect(98, 7, 112, 21, OLED_CLEAR);
      }
      if (num2 >= 10 && num1 < 10) {
        oled.rect(84, 7, 98, 21, OLED_CLEAR);
      }
      oled.print("Pot");
      oled.print(num + 1);
      oled.print(":");
    }
    if (num > 7) {
      if (num2 >= 100 && num1 < 100) {
        oled.rect(112, 7, 126, 21, OLED_CLEAR);
      }
      if (num2 >= 10 && num1 < 10) {
        oled.rect(98, 7, 112, 21, OLED_CLEAR);
      }
      oled.print("Fade");
      oled.print(num - 7);
      oled.print(":");
    }
    oled.print(num1);
    flag2 = 0;
  }
}

int analogReadStab(byte analogPin) {
  long sum = 0;
  for (int p = 0; p <= 255; p++) {
    sum += analogRead(analogPin);
  }
  sum = sum >> 8;
  return sum;
}
