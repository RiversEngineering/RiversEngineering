/*****************************************************
 * 
 * Rivers Motor Controller Library
 * Yoshiro Fujita, 2019
 * For use in The Rivers School Robotics program
 * 
 * Implements a class that serves to simplify the use
 * of an H-Bridge DC motor controller through two pins:
 * DIRection and PWM. Written specifically for use with
 * the Cytron MDD10A Dual Channel Motor Controller.
 * 
 * The Motor class controls a single channel of the motor 
 * controller, for use with a single motor. Multiple
 * objects should be instantiated for use with multiple
 * motors.
 * 
 * Also creates predefined macros for use with the 
 * custom Arduino shield currently in development.
 * 
 * Also makes use of the EnableInterrupt library, though
 * this functionality is currently in development and is
 * not fully tested.
 * 
 *****************************************************/
#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H
#ifndef MOTOR_H
#define MOTOR_H

#include "RiversIO.h"



/////////////////////////////// Custom PCB Macros ///////////////////////////////
//m2 is MCA
#define MCA1 2, 3
#define MCA2 12, 11
#define MCB1 4, 5
#define MCB2 7, 6

#define MCA_1 2, 3
#define MCA_2 12, 11
#define MCB_1 4, 5
#define MCB_2 7, 6

#define MC_SERVO_AB 8, 9
#define MC_SERVO_CD 13, 10



///////////////////////////////  Interrupt Macros ///////////////////////////////
#ifdef ENABLE_INTERRUPT
#include <EnableInterrupt.h>

int PPR = 280;

#define PINCOUNT(x) pin ##x ##Count
#define INCREMENT(x) pin ##x ##Increment
#define interruptFunction(x) \
  volatile long PINCOUNT(x); \
  volatile long INCREMENT(x) = 1; \
  void interruptFunction ##x () { \
    PINCOUNT(x)++; \
  }

//=INCREMENT(x); \

#define updateOn(x) \
  PINCOUNT(x)=0;


#define setupInterrupt(x) \
  pinMode( x, INPUT_PULLUP); \
  enableInterrupt( x, interruptFunction##x, RISING)

interruptFunction(A0);
interruptFunction(A1);
interruptFunction(A2);
interruptFunction(A3);
interruptFunction(13);

#endif


///////////////////////////////////////////////////////////////////////////
/////////////////////////////// Motor Class ///////////////////////////////

// Implements a class for controlling a single motor via
// a direction pin and a PWM pin.
class Motor : public Output {
  public:
    /////////////////////////////// Constructors ///////////////////////////////
    Motor() {}
    Motor(uint8_t dir, uint8_t pwm) {
      this->attachDIR(dir);
      this->attachPWM(pwm);
    };
    //////////////////////////////// Set Speed /////////////////////////////////
    int set(int speed) {
      if (speed > 255)
        speed = 255;
      else if (speed < -255)
        speed = -255;

      digitalWrite(_dir, (speed > 0) ? HIGH : LOW);
      analogWrite(_pwm, abs(speed));
      if (_encoderIncVar != NULL) {
        if (_dir)
          *_encoderIncVar = 1;
        else
          *_encoderIncVar = -1;
      }
      return speed;
    };
    int setSpeed(int speed) {
      return this->set(speed);
    };
    int write(int speed) {
      return this->set(speed);
    };
    int writeSpeed(int speed) {
      return this->set(speed);
    };
    int setMotor(int speed) {
      return this->set(speed);
    };
    //////////////////////////////// Attach Pins ///////////////////////////////
    void attachDIR(uint8_t dir) {
      _dir = dir;
      pinMode(_dir, OUTPUT);
    };
    void attachPWM(uint8_t pwm) {
      _pwm = pwm;
      pinMode(_pwm, OUTPUT);
    };
    void attachWhite(uint8_t pin) {
      this->attachDIR(pin);
    };
    void attachGreen(uint8_t pin) {
      this->attachDIR(pin);
    };
    void attachYellow(uint8_t pin) {
      this->attachPWM(pin);
    };
    void attachBlue(uint8_t pin) {
      this->attachPWM(pin);
    };
    void attach(uint8_t dir, uint8_t pwm) {
      this->attachDIR(dir);
      this->attachPWM(pwm);

      pinMode(_dir, OUTPUT);
      pinMode(_pwm, OUTPUT);
    }
    void isAttachedTo(uint8_t dir, uint8_t pwm) {
      this->attach(dir, pwm);
    }
    void dirIsAttachedTo(uint8_t dir) {
      this->attachDIR(dir);
    }
    void pwmIsAttachedTo(uint8_t pwm) {
      this->attachPWM(pwm);
    }


#ifdef ENABLE_INTERRUPT
    // Encoders tracking
    void enableEncoder(uint8_t pin) {
      switch (pin) {
        case A0:
          setupInterrupt(A0);
          updateOn(A0);
          _encoderIncVar = & INCREMENT(A0);
          _encoderCount = & PINCOUNT(A0);
          break;
        case A1:
          setupInterrupt(A1);
          updateOn(A1);
          _encoderIncVar = & INCREMENT(A1);
          _encoderCount = & PINCOUNT(A1);
          break;
        case A2:
          setupInterrupt(A2);
          updateOn(A2);
          _encoderIncVar = & INCREMENT(A2);
          _encoderCount = & PINCOUNT(A2);
          break;
        case A3:
          setupInterrupt(A3);
          updateOn(A3);
          _encoderIncVar = & INCREMENT(A3);
          _encoderCount = & PINCOUNT(A3);
          break;
        case 13:
          setupInterrupt(13);
          updateOn(13);
          _encoderIncVar = & INCREMENT(13);
          _encoderCount = & PINCOUNT(13);
          break;
      }
      *_encoderIncVar = 1;
    }

    long getCount() {
      return *_encoderCount;
    }
    long getRevs() {
      return this->getCount() / PPR;
    }
    int getAngle() {
      int partialTicks = this->getCount() % PPR;

      return partialTicks * 360 / PPR;
    }
    void resetEncoderCount(long x) {
      if (_encoderCount != NULL)
        *_encoderCount = x;
    }
    void resetEncoderCount() {
      this->resetEncoderCount(0);
    }
#endif

    /////////////////////////////////// Private //////////////////////////////////
  private:
    uint8_t _pwm, _dir;
    long* _encoderIncVar;
    long* _encoderCount;

};
#endif
#endif
