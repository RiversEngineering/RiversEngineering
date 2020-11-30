/*  Basic Timer
 *  Fuj, 2020
 *  
 *  This program shows the basic usage of a Timer
 */
#include <RiversEngineering.h>
Timer countdown;
Buzzer alarm;

void setup() {
  alarm.isAttachedTo(11);
  
  // set a coundown timer for 5000 ms (5 seconds)
  countdown.set(5000);
  countdown.start();

}


void loop() {
  if (countdown.isDone()) {
    alarm.play();
  }
}
