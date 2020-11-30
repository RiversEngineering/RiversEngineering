/*  Basic Servo
 *  Fuj, 2020
 *  
 *  This program shows the basic usage of a servomotor
 */
#include <RiversEngineering.h>

Servomotor servo;


void setup() {
  servo.isAttachedTo(12);
}


void loop() {
  servo.set(90);
  delay(500);
  servo.set(45);
  delay(500);
}
