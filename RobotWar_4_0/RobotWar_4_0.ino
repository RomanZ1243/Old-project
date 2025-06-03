#define MRF1 1
#define MRF2 1
#define MLF1 1
#define MLF2 1
#define MRB1 1
#define MRB2 1
#define MLB1 1
#define MLB2 1
#define GUN 1

#include <IBusBM.h>
IBusBM IBus;    // IBus object

int stX;
int stY;
int rud;
int swA;
int swD;
int vrA;
int vrB;


void setup() {
  IBus.begin(Serial);    // iBUS object connected to serial0 RX pin
  pinMode(MRF1, OUTPUT);
  pinMode(MRF2, OUTPUT);
  pinMode(MLF1, OUTPUT);
  pinMode(MLF2, OUTPUT);
  pinMode(MRB1, OUTPUT);
  pinMode(MRB2, OUTPUT);
  pinMode(MLB1, OUTPUT);
  pinMode(MLB2, OUTPUT);
  pinMode(GUN, OUTPUT);
}

void loop() {
  IBus.loop();
  stX = IBus.readChannel(0);
  stY = IBus.readChannel(1);
  rud = IBus.readChannel(3);
  swA = IBus.readChannel(4);
  swD = IBus.readChannel(5);
  vrA = IBus.readChannel(6);
  vrB = IBus.readChannel(7);
}
