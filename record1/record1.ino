#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>

#define SD_ChipSelectPin 10

TMRpcm audio;
Sd2Card card;
SdVolume volume;
SdFile root;
const int chipSelect = 10;
int audiofile = 0;
unsigned long i = 0;
bool recmode = 0;
int x;

void setup() {
  Serial.begin(9600);
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }
  pinMode(A0, INPUT);
  pinMode(6, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  //attachInterrupt(0, button, LOW);
  SD.begin(SD_ChipSelectPin);
  audio.CSPin = SD_ChipSelectPin;
}

void loop() {
  if (x == 0) {
    digitalWrite(6, LOW);
    if (digitalRead(2) == 0) {
      x = 1;
    }
  }
  if (x == 1) {
    digitalWrite(6, HIGH);
    audio.startRecording("1.wav", 16000, A0);
    delay(5000);
    audio.stopRecording("1.wav");
    x = 0;
  }
}

/*void button() {
  while (i < 300000) {
    i++;
  }
  i = 0;
  if (recmode == 0) {
    recmode = 1;
    audiofile++;
    digitalWrite(6, HIGH);
    switch (audiofile) {
      case 1: audio.startRecording("1.wav", 16000, A0); break;
      case 2: audio.startRecording("2.wav", 16000, A0); break;
      case 3: audio.startRecording("3.wav", 16000, A0); break;
      case 4: audio.startRecording("4.wav", 16000, A0); break;
      case 5: audio.startRecording("5.wav", 16000, A0); break;
      case 6: audio.startRecording("6.wav", 16000, A0); break;
      case 7: audio.startRecording("7.wav", 16000, A0); break;
      case 8: audio.startRecording("8.wav", 16000, A0); break;
      case 9: audio.startRecording("9.wav", 16000, A0); break;
      case 10: audio.startRecording("10.wav", 16000, A0); break;
    }
  }
  else {
    recmode = 0;
    digitalWrite(6, LOW);
    switch (audiofile) {
      case 1: audio.stopRecording("1.wav"); break;
      case 2: audio.stopRecording("2.wav"); break;
      case 3: audio.stopRecording("3.wav"); break;
      case 4: audio.stopRecording("4.wav"); break;
      case 5: audio.stopRecording("5.wav"); break;
      case 6: audio.stopRecording("6.wav"); break;
      case 7: audio.stopRecording("7.wav"); break;
      case 8: audio.stopRecording("8.wav"); break;
      case 9: audio.stopRecording("9.wav"); break;
      case 10: audio.stopRecording("10.wav"); break;
    }
  }
  }*/
