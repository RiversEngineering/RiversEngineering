/*  Basic Button
 *  Fuj, 2020
 *  
 *  This program shows the basic usage of a button
 *  to control an RGB LED.
 */
#include <RiversEngineering.h>

LED myLED; 
Button myButton;

void setup() {
  myLED.isAttachedTo(11);
  myButton.isAttachedTo(12);
}


void loop() {
  if (myButton.isPressed()) {
    myLED.set(RGB_BLUE);
  }
  else {
    myLED.set(RGB_OFF);
  }
}
