/*
   MIDIUSB_test.ino

   Created: 4/6/2015 10:47:08 AM
   Author: gurbrinder grewal
   Modified by Arduino LLC (2015)
*/

#include "MIDIUSB.h"

int flag;
int flag1;
int flag2;
int flag3;

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

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
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() {
  if (digitalRead(9) == 0 && flag == 0) {
    noteOn(0, 48, 127);   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    flag = 1;
  }
  if (digitalRead(9) == 1 && flag == 1) {
    noteOff(0, 48, 127);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    flag = 0;
  }
  if (digitalRead(10) == 0 && flag1 == 0) {
    noteOn(0, 50, 127);   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    flag1 = 1;
  }
  if (digitalRead(10) == 1 && flag1 == 1) {
    noteOff(0, 50, 127);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    flag1 = 0;
  }
  if (digitalRead(11) == 0 && flag2 == 0) {
    noteOn(0, 52, 127);   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    flag2 = 2;
  }
  if (digitalRead(11) == 1 && flag2 == 1) {
    noteOff(0, 52, 127);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    flag2 = 0;
  }
  if (digitalRead(12) == 0 && flag3 == 0) {
    noteOn(0, 54, 127);   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    flag3 = 1;
  }
  if (digitalRead(12) == 1 && flag3 == 1) {
    noteOff(0, 54, 127);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    flag3 = 0;
  }
  // controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65
}
