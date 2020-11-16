/*****************************************************
 * 
 * Rivers Time Library
 * Yoshiro Fujita, 2019
 * For use in The Rivers School Engineering program
 * 
 * Implements classes to simplify the use of millis()
 * for beginning students. Implements a stopwatch class 
 * that tracks elapsed time since start. Also implements 
 * a countdown timer class that can be checked periodically 
 * to see if it has expired. Neither class makes use of 
 * any custom interrupts, only the millis() function,
 * and thus must be polled regularly.
 * 
 *****************************************************/
#ifndef TIME_H
#define TIME_H
#include "RiversIO.h"



long currentTime() {
  return millis();
};



/*******************************************************************************
                                                        Stopwatch class

  Class to keep track of time elapsed (in milliseconds) in a more intuitive way
  for students unfamiliar with programming.
 *******************************************************************************/
class Stopwatch : public Input {
  private:
    long startTime = 0;
  public:
    Stopwatch() {};
    void start() {
      startTime = millis();
    }
    void reset() {
      this->start();
    }
    void restart() {
      this->start();
    }
    long elapsedMillis() {
      return (millis() - startTime);
    }
    double elapsedSeconds() {
      return this->elapsedMillis() / 1000.0;
    }
    int read() {
      return elapsedMillis();
    }
};

/*******************************************************************************
                                                        Timer class

  Class implements a countdown timer (in milliseconds) to make time tracking
  easier and more intuitive for students.
 *******************************************************************************/
class Timer : public Input {
  private:
    long startTime;
    long waitTime;

  public:
    Timer() {}
    Timer(long length) {
      this->setLength(length);
    }
    Timer(int length) {
      this->setLength(length);
    }
    void setLength(long length) {
      waitTime = length;
    }
    void start() {
      startTime = millis();
    }
    boolean isDone() {
      return (millis() > startTime + waitTime);
    }
    boolean isNotDone() {
      return !this->isDone();
    }
    int read() {
      return this->isDone();
    }
};

#endif
