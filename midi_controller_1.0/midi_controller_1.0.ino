#include <CD74HC4067.h>
#include <LineDriver.h>
#include <SPI.h>
#include <SPI_Bus.h>
#include <MIDIUSB.h>

CD74HC4067 mux(2, 3, 4, 5);
SPI_Bus reg(_32bit, 10, MSBFIRST);

boolean flag[] = {0};
const int NPots = 5;

int potCState[NPots] = {0}; // Current state of the pot; delete 0 if 0 pots
int potPState[NPots] = {0}; // Previous state of the pot; delete 0 if 0 pots
int potVar = 0; // Difference between the current and previous state of the pot
int midiCState[NPots] = {0}; // Current state of the midi value; delete 0 if 0 pots
int midiPState[NPots] = {0}; // Previous state of the midi value; delete 0 if 0 pots
const int TIMEOUT = 300; //* Amount of time the potentiometer will be read after it exceeds the varThreshold
const int varThreshold = 10; //* Threshold for the potentiometer signal variation
boolean potMoving = true; // If the potentiometer is moving
unsigned long PTime[NPots] = {0}; // Previously stored time; delete 0 if 0 pots
unsigned long timer[NPots] = {0}; // Stores the time that has elapsed since the timer was reset; delete 0 if 0 pots
byte midiCh = 1; //* MIDI channel to be used

byte note = 36; //* Lowest note to be used; 36 = C2; 60 = Middle C
byte cc = 1; //* Lowest MIDI CC to be used

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
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() {
static uint32_t last_input_states = 0;
  uint32_t states = reg.read32bits();
  if (states != last_input_states) {
    uint32_t changed = states ^ last_input_states;
    last_input_states = states;
    for (int i = 0; i < reg.bandwidth() * 8; ++i) {
      if ((i == 0   || // 3A
           i == 1) && (changed & 1)) {
        //Serial.println(i);
        //Serial.println(i);
        flag[i] = !flag[i];
        if (flag[i] == 0) {
          noteOn(0, 1 + i, 127);  // Channel 0, middle C, normal velocity
          MidiUSB.flush();
        }
        else if (flag[i] == 1) {
          noteOff(0, 1 + i, 127);   // Channel 0, middle C, normal velocity
          MidiUSB.flush();
        }
      }
      changed >>= 1;
      states >>= 1;
    }
  }
  potentiometers();
}

void potentiometers() {
  for (int i = 0; i < NPots; i++) {
    mux.channel(i);
    potCState[i] = analogRead(A0);

    midiCState[i] = map(potCState[i], 0, 1023, 0, 127);
    if (midiCState[i] == 126) {
      midiCState[i] = 127;
    }
    potVar = abs(potCState[i] - potPState[i]);

    if (potVar > varThreshold) {
      PTime[i] = millis();
    }

    timer[i] = millis() - PTime[i];

    if (timer[i] < TIMEOUT) {
      potMoving = true;
    }
    else {
      potMoving = false;
    }

    if (potMoving == true) {
      if (midiPState[i] != midiCState[i]) {
        controlChange(midiCh, cc + i, midiCState[i]);
        MidiUSB.flush();

        potPState[i] = potCState[i];
        midiPState[i] = midiCState[i];
      }
    }
  }
}
