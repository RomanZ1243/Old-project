#include <CD74HC4067.h>
#include <MIDIUSB.h>

// Инициализация объекта мультиплексора CD74HC4067 с пинами управления (s0, s1, s2, s3)
CD74HC4067 mux(4, 5, 6, 7);

int val[17];
int val_old[17];

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
  // Начинаем взаимодействие с монитором порта (серийным портом) на скорости 9600 бит/с
  Serial.begin(115200);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() {
  // Цикл для переключения мультиплексора между каналами 0-15
  for (int i = 0; i <= 16; i++) {
    mux.channel(i); // Устанавливаем мультиплексор на канал i

    val_old[i] = val[i];
    if (i <= 15) {
      val[i] = map(analogRead(A0), 0, 1023, 0, 127);
    }
    if (i == 16) {
      val[i] = map(analogRead(A2), 0, 1023, 0, 127);
    }
    //val[i] = analogReadStab(val[i]);
    if (val[i] != val_old[i]) {
      controlChange(1, 30 + i, val[i]);   // Channel 0, middle C, normal velocity
      MidiUSB.flush();
    }
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
