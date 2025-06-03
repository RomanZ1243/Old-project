#include <LineDriver.h>
#include <SPI.h>
#include <SPI_Bus.h>
#include <MIDIUSB.h>
SPI_Bus reg(_24bit, A1, MSBFIRST);

boolean flag[24];
boolean flag1[24];

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
  Serial.begin(9600);
  reg.setSelectionPolicy(SPI_Bus::SELECT_BEFORE);
}

void loop() {
  static uint32_t last_input_states = 0;
  uint32_t states = reg.read32bits();
  if (states != last_input_states) {
    uint32_t changed = states ^ last_input_states;
    last_input_states = states;
    for (int i = 0; i < reg.bandwidth() * 8; ++i) {
      if ((i >= 0 && i <= 23) && (changed & 1)) {
        //Serial.println(i);
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
