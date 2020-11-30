/*  Basic Timer
 *  Fuj, 2020
 *  
 *  This program shows the basic usage of a Timer
 */
#include <RiversEngineering.h>
Stopwatch count;
Buzzer buzz;

int t;

void setup() {
  buzz.isAttachedTo(11);

  // start the stopwatch
  count.start();
}


void loop() {
  // read the stopwatch in milliseconds
  t = count.read();

  // every 1 second, play a 200 ms long tone at 110 Hz
  if (t < 200) {
    buzz.play(110);
  }
  else {
    buzz.stop();
    if (t >= 1000) {
      count.reset();
    }
  }
}
