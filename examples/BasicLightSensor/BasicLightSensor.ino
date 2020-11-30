/*  Basic Potentiometer
    Fuj, 2020

    This program shows the basic usage of a potentiometer
*/
#include <RiversEngineering.h>

LightSensor light;
Buzzer myBuzzer;

int lightReading;

void setup() {
  light.isAttachedTo(A1);
  myBuzzer.isAttachedTo(11);
}


void loop() {
  lightReading = light.read();
  if (lightReading < 200) {
    myBuzzer.play();
  }
}
