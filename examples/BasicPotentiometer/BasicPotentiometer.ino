/*  Basic Potentiometer
 *  Fuj, 2020
 *  
 *  This program shows the basic usage of a potentiometer
 */
#include <RiversEngineering.h>

Potentiometer knob;
LED myLED;

int knobReading;
int brightness;

void setup() {
  knob.isAttachedTo(A1);
  myLED.isAttachedTo(12);
}


void loop() {
  knobReading = knob.read();
  brightness = knobReading / 4;
  myLED.set(brightness, 0, 0);
}
