/*
   Ultrasonic.h

   Library for Ultrasonic Ranging Module in a minimalist way

   created 3 Apr 2014
   by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
   modified 23 Jan 2017
   by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
   modified 04 Mar 2017
   by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
   modified 15 May 2017
   by Eliot Lim    (github: @eliotlim)
   modified 10 Jun 2018
   by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)


   Released into the MIT License.

   Modified 2019 by Yoshiro Fujita to change method names and make
   consistent with other Rivers School Libraries. Also includes some 
   HCSR04 code from the Arcbotics Sparki library, in the interest of 
   comparing different data collection methods and for consistency
   in the transition from using Sparki to creating custom robots
   in the Rivers Robotics classes. All due credit to said authors.
*/


#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include "RiversIO.h"


#define SPARKI_PING

/*******************************************************************************
                                                        Ultrasonic class

   Modifies the Ultrasonic class to match the method conventions established
   for other classes in other libraries.
 *******************************************************************************/
class Ultrasonic : Input {
  private:
    uint8_t Trig_pin;
    uint8_t Echo_pin;
    long  duration, distacne_cm, distance_inc, previousMicros;
    long maxWaitTime = 58000;
    long timeout = 20000;
    uint8_t samples = 5;
  public:
    /*
      Ultrasonic.cpp - Library for HC-SR04 Ultrasonic Ranging Module.library

      Created by ITead studio. Apr 20, 2010.
      iteadstudio.com

      Modified by Yoshi Fujita so that timeout returns -1. Oct 27, 2016
      Also added default ping() method in cm
      Further adapted to use a common system of attach() members March 2018
    */
    Ultrasonic() {};
    void attach(uint8_t trig, uint8_t echo) {
      pinMode(trig, OUTPUT);
      pinMode(echo, INPUT);
      Trig_pin = trig;
      Echo_pin = echo;
    }
    void attachTrigger(uint8_t trig) {
      pinMode(trig, OUTPUT);
      Trig_pin = trig;
    }
    void attachEcho(uint8_t echo) {
      pinMode(echo, INPUT);
      Echo_pin = echo;
    }
    void trigIsAttachedTo(uint8_t trig) {
      this->attachTrigger(trig);
    }
    void echoIsAttachedTo(uint8_t echo) {
      this->attachTrigger(echo);
    }
    void isAttachedTo(uint8_t trig, uint8_t echo) {
      this->attach(trig, echo);
    }
    long Timing()
    {
      digitalWrite(Trig_pin, LOW);
      delayMicroseconds(2);
      digitalWrite(Trig_pin, HIGH);
      delayMicroseconds(10);
      digitalWrite(Trig_pin, LOW);

      //      duration = pulseIn(Echo_pin, HIGH, maxWaitTime); //timeout after 58000 µs
      //      return duration;


      previousMicros = micros();
      while (!digitalRead(Echo_pin) && (micros() - previousMicros) <= timeout); // wait for the echo pin HIGH or timeout
      previousMicros = micros();
      while (digitalRead(Echo_pin)  && (micros() - previousMicros) <= timeout); // wait for the echo pin LOW or timeout

      return micros() - previousMicros; // duration
    }
    int simplePing() {
      return Timing() / 28 / 2;
    }


    float ping_single() {
      long duration;
      float cm;
      digitalWrite(Trig_pin, LOW);
      delayMicroseconds(2);
      digitalWrite(Trig_pin, HIGH);
      delayMicroseconds(10);
      digitalWrite(Trig_pin, LOW);


      uint8_t bit = digitalPinToBitMask(Echo_pin);
      uint8_t port = digitalPinToPort(Echo_pin);
      uint8_t stateMask = (HIGH ? bit : 0);

      unsigned long startCount = 0;
      unsigned long endCount = 0;
      unsigned long width = 0; // keep initialization out of time critical area

      // convert the timeout from microseconds to a number of times through
      // the initial loop; it takes 16 clock cycles per iteration.
      unsigned long numloops = 0;
      unsigned long maxloops = 5000;

      // wait for any previous pulse to end
      while ((*portInputRegister(port) & bit) == stateMask)
        if (numloops++ == maxloops)
          return -1;

      // wait for the pulse to start
      while ((*portInputRegister(port) & bit) != stateMask)
        if (numloops++ == maxloops)
          return -1;

      startCount = micros();
      // wait for the pulse to stop
      while ((*portInputRegister(port) & bit) == stateMask) {
        if (numloops++ == maxloops)
          return -1;
        delayMicroseconds(10); //loop 'jams' without this
        if ((micros() - startCount) > 58000 ) { // 58000 = 1000CM
          return -1;
          break;
        }
      }
      duration = micros() - startCount;
      //--------- end pulsein
      cm = (float)duration / 29.0 / 2.0;
      return (cm);
    };

    float ping() {
      int attempts = samples;
      float distances [attempts];
      for (int i = 0; i < attempts; i++) {
        distances[i] = ping_single();
        delay(20);
      }

      // sort them in order
      float temp;

      for (int i = (attempts - 1); i > 0; i--)
      {
        for (int j = 1; j <= i; j++)
        {
          if (distances[j - 1] > distances[j])
          {
            temp = distances[j - 1];
            distances[j - 1] = distances[j];
            distances[j] = temp;
          }
        }
      }

      // return the middle entry
      return (distances[(int)ceil((float)attempts / 2.0)]);

      return -2;
    };
    int read() {
      return this->ping();
    }
    void setMaxWaitTime(long t) {
      maxWaitTime = t;
    };
    void setMaxDistance(int d) {
      long t = d * 2 * 29;
      this->setMaxWaitTime(t);
    };
    void setNumSamples(int n) {
      if (n % 2 != 1)
        n++;
      samples = n;
    };
};

#endif
