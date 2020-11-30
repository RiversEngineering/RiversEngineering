/*  Basic Buzzer
 *  Fuj, 2020
 *  
 *  This program shows the basic usage of a buzzer.
 *  
 */
#include <RiversEngineering.h>  


Buzzer myBuzzer; 


void setup() {
  // Tell the Arduino what pin we've connected the buzzer to
  myBuzzer.isAttachedTo(11);

}


void loop() {
  myBuzzer.play();
  delay(200);
  myBuzzer.stop();
  delay(800);
}
