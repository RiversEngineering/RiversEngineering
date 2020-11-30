/*  Basic Distance Sensor
 *  Fuj, 2020
 *  
 *  This program shows the basic usage of a ToF Distance Sensor
 */
#include <RiversEngineering.h>

DistanceSensor distance;
Display screen;

int distReading;

void setup() {
  distance.begin();
  screen.begin();
  screen.clearScreen();
}


void loop() {
  // take a reading and print it
  distReading = distance.read();
  screen.setTextColor(TFT_WHITE);
  screen.print(distReading);
  
  // wait a bit
  delay(200);

  // print the same thing but in black to cover up the old number
  screen.setTextColor(TFT_BLACK);
  screen.print(distReading);
}
