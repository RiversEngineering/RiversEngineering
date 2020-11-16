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

 *
 *****************************************************/
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



///////////////////////////////////////////////////////////////////////////
/////////////////////////////// Motor Class ///////////////////////////////

// Implements a class for controlling a single motor via
// a direction pin and a PWM pin.
class Motor : public Output {
  public:
    /////////////////////////////// Constructors ///////////////////////////////
    Motor();
    Motor(uint8_t dir, uint8_t pwm);
    //////////////////////////////// Set Speed /////////////////////////////////
    int set(int speed);
    int setSpeed(int speed);
    int write(int speed);
    int writeSpeed(int speed);
    int setMotor(int speed);
    //////////////////////////////// Attach Pins ///////////////////////////////
    void attachDIR(uint8_t dir);
    void attachPWM(uint8_t pwm);
    void attach(uint8_t dir, uint8_t pwm);
    void isAttachedTo(uint8_t dir, uint8_t pwm);
    void dirIsAttachedTo(uint8_t dir);
    void pwmIsAttachedTo(uint8_t pwm);


    /////////////////////////////////// Private //////////////////////////////////
  private:
    uint8_t _pwm, _dir;

};

#endif
