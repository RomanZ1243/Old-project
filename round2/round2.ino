/*

 Arduino TFT Bitmap Logo example

 This example reads an image file from a micro-SD card
 and draws it on the screen, at random locations.

 In this sketch, the Arduino logo is read from a micro-SD card.
 There is a .bmp file included with this sketch.
 - open the sketch folder (Ctrl-K or Cmd-K)
 - copy the "arduino.bmp" file to a micro-SD
 - put the SD into the SD slot of the Arduino TFT module.

 This example code is in the public domain.

 Created 19 April 2013 by Enrico Gueli

 http://www.arduino.cc/en/Tutorial/TFTBitmapLogo

 */

// include the necessary libraries
#include <SPI.h>
#include <SD.h>
#include <TFT.h>  // Arduino LCD library

// pin definition for the Uno
#define sd_cs  4
#define lcd_cs 10
#define dc     9
#define rst    8

// pin definition for the Leonardo
//#define sd_cs  8
//#define lcd_cs 7
//#define dc     0
//#define rst    1

int x1;
int y1;
int a;
int r;
int l;

TFT TFTscreen = TFT(lcd_cs, dc, rst);

// this variable represents the image to be drawn on screen

void setup() {
  // initialize the GLCD and show a message
  // asking the user to open the serial line
  TFTscreen.begin();
  TFTscreen.background(255, 255, 255);
  a = 45;
  r = 60;
  l = 10;
  x1 = cos(radians(a)) * (r - l) + 80;
  y1 = sin(radians(a)) * (r - l) + 64;
  TFTscreen.stroke(255, 0, 0);
  TFTscreen.circle(80, 64, r);
  TFTscreen.line(80, 64, x1, y1);
  
}

void loop() {
}
