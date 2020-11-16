/*****************************************************
 *
 * Rivers Servomotor Library
 * Yoshiro Fujita, 2019
 * For use in The Rivers School Engineering program
 *
 * Creates a subclass called Servomotor, which inherits
 * the Servo class that is built in to Arduino. Done
 * primarily so that the syntax and methods are consistent
 * with the rest of the libraries to make things more
 * intuitive for beginning students. Also puts limits
 * on angles to prevent damage to servos from inputs
 * beyond the servo's mechanical range.
 *
 * Additionally defines macros for use with custom
 * Arduino shield for robotics, still in development.
 *
 *****************************************************/
#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Servo.h>
#include "RiversIO.h"

#define SERVO_A 9
#define SERVO_B 8
#define SERVO_C 13
#define SERVO_D 10

#define ANALOG_A A0
#define ANALOG_B A1
#define ANALOG_C A2
#define ANALOG_D A3

/*******************************************************************************
                                                        Servomotor class
 *******************************************************************************/
class Servomotor : public Servo, public Output{
  private:
    int _maxAngle = 180;
    int _minAngle = 0;

  public:
    Servomotor();
    Servomotor(uint8_t pin);
    void isAttachedTo(uint8_t pin);
    void set(int angle);
    void setMin(int min);
    void setMax(int max);
    void setMinMax(int min, int max);
};

#endif
