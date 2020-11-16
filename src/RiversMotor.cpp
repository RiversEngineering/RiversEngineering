#include "RiversMotor.h"


/////////////////////////////// Constructors ///////////////////////////////
Motor::Motor() {}
Motor::Motor(uint8_t dir, uint8_t pwm) {
  this->attachDIR(dir);
  this->attachPWM(pwm);
}
//////////////////////////////// Set Speed /////////////////////////////////
int Motor::set(int speed) {
  if (speed > 255)
  speed = 255;
  else if (speed < -255)
  speed = -255;

  digitalWrite(_dir, (speed > 0) ? HIGH : LOW);
  analogWrite(_pwm, abs(speed));
  return speed;
}
int Motor::setSpeed(int speed) {
  return this->set(speed);
}
int Motor::write(int speed) {
  return this->set(speed);
}
int Motor::writeSpeed(int speed) {
  return this->set(speed);
}
int Motor::setMotor(int speed) {
  return this->set(speed);
}
//////////////////////////////// Attach Pins ///////////////////////////////
void Motor::attachDIR(uint8_t dir) {
  _dir = dir;
  pinMode(_dir, OUTPUT);
}
void Motor::attachPWM(uint8_t pwm) {
  _pwm = pwm;
  pinMode(_pwm, OUTPUT);
}
void Motor::attach(uint8_t dir, uint8_t pwm) {
  this->attachDIR(dir);
  this->attachPWM(pwm);

  pinMode(_dir, OUTPUT);
  pinMode(_pwm, OUTPUT);
}
void Motor::isAttachedTo(uint8_t dir, uint8_t pwm) {
  this->attach(dir, pwm);
}
void Motor::dirIsAttachedTo(uint8_t dir) {
  this->attachDIR(dir);
}
void Motor::pwmIsAttachedTo(uint8_t pwm) {
  this->attachPWM(pwm);
}
