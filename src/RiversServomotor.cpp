#include "RiversServomotor.h"

Servomotor::Servomotor(){};
Servomotor::Servomotor(uint8_t pin) {
  this->attach(pin);
}
void Servomotor::isAttachedTo(uint8_t pin) {
  this->attach(pin);
}
void Servomotor::set(int angle) {
  if (angle > _maxAngle)
    angle = _maxAngle;
  else if (angle < _minAngle)
    angle = _minAngle;

  this->write(angle);
}
void Servomotor::setMin(int min) {
  _minAngle = min;
}
void Servomotor::setMax(int max) {
  _maxAngle = max;
}
void Servomotor::setMinMax(int min, int max) {
  this->setMin(min);
  this->setMax(max);
}
