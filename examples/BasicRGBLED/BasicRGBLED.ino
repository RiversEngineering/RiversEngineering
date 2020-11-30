/*  Basic RGB LED
 *  Fuj, 2020
 *  
 *  This program shows the basic usage of an RGB LED.
 */
#include <RiversEngineering.h>

LED myLED; 

void setup() {
  myLED.isAttachedTo(12);
}


void loop() {
  myLED.setColor(RGB_RED);
  delay(500);
  myLED.setColor(RGB_OFF);
  delay(500);
}
