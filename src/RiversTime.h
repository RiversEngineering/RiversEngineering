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



/*******************************************************************************
                                                        Stopwatch class

  Class to keep track of time elapsed (in milliseconds) in a more intuitive way
  for students unfamiliar with programming.
 *******************************************************************************/
class Stopwatch : public Input {
  private:
    long startTime = 0;
  public:
    Stopwatch();
    void start();
    void reset();
    void restart();
    long elapsedMillis();
    double elapsedSeconds();
    int read();
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
    Timer();
    Timer(long length);
    Timer(int length);
    void setLength(long length);
    void start();
    boolean isDone();
    boolean isNotDone();
    int read();
};

#endif
