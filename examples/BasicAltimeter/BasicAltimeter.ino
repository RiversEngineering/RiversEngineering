/*  Basic Altimeter
 *  Fuj, 2020
 *  
 *  This program shows the basic usage of an Altimeter
 */
#include <RiversEngineering.h>
Altimeter alt;
Display screen;

float altReading;
float prev;

float temp;
int li = 3;

void setup() {
  alt.begin();
  screen.begin();
  screen.clearScreen();
}


void loop() {
  altReading = alt.readAltitude();
  myPrint(altReading);
  delay(100);
}



void myPrint(float x) {
  // overwrite the previous number
  screen.setTextColor(TFT_BLACK);
  screen.print(prev);

  // write the new number
  screen.setTextColor(TFT_WHITE);
  screen.print(x);

  // store new number as previous for next time
  prev = x;
}
