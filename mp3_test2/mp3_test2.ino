#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(2, 3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);
  myDFPlayer.volume(2);  //Set volume value. From 0 to 30
}

void loop() {
  myDFPlayer.playFolder(1, 1);
  delay(2000);
  myDFPlayer.playFolder(1, 2);
  delay(2000);
  myDFPlayer.playFolder(2, 1);
  delay(2000);
  myDFPlayer.playFolder(2, 2);
  delay(2000);
}
