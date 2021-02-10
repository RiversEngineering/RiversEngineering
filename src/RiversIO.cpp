#include "RiversIO.h"



/*******************************************************************************
                                                        Button class

  For use with buttons that when pressed connect an input pin to ground.
  Can detect transitions from not pressed to pressed (HIGH -> LOW)
  or from pressed to not pressed (LOW -> HIGH)
 *******************************************************************************/

Button::Button() {};
void Button::attach(int p) {
  pin = p;
  pinMode(pin, INPUT_PULLUP);
  delay(200);
}
void Button::isAttachedTo(int p) {
  this->attach(p);
}
int Button::read() {
  return digitalRead(pin);
}
void Button::setPressedState(boolean ps) {
  pressedState = ps;
}
boolean Button::isPressed() {
  return digitalRead(pin) == pressedState;
}
boolean Button::transitionPressed() {
  if (digitalRead(pin) == pressedState) {
    if (!wasPressedLast) {
      return true;
    }
    wasPressedLast = true;
  }
  else wasPressedLast = false;
  return false;
}
boolean Button::transitionReleased() {
  if (digitalRead(pin) == !pressedState) {
    if (wasPressedLast) {
      return true;
    }
    wasPressedLast = false;
  }
  else wasPressedLast = true;
  return false;
}




/*******************************************************************************
                                                        LED class

  For use with simple LEDs connected to an input pin.
  Can be configured so that HIGH turns the LED on (default), or LOW.
  Also can use PWM pins for varying brightness.
  Don't forget to use a current limiting resistor so LEDs aren't blown out.
 *******************************************************************************/

Buzzer::Buzzer() {};
void Buzzer::attach(int p) {
  pin = p;
  pinMode(pin, OUTPUT);
  delay(200);
}
void Buzzer::isAttachedTo(int p) {
  this->attach(p);
}
void Buzzer::play(int f) {
  if (frequency != f)
    tone(pin, f);
  frequency = f;
}
void Buzzer::play() {
  if (frequency != 110)
    this->play(110);
frequency = 110;
}
void Buzzer::stop() {
  noTone(pin);
  frequency = -1;
}



/*******************************************************************************
                                                      Simple LED class

  For use with simple LEDs connected to an input pin.
  Can be configured so that HIGH turns the LED on (default), or LOW.
  Also can use PWM pins for varying brightness.
  Don't forget to use a current limiting resistor so LEDs aren't blown out.
 *******************************************************************************/

SimpleLED::SimpleLED() {};
void SimpleLED::attach(int p) {
  pin = p;
  pinMode(pin, OUTPUT);
}
void SimpleLED::isAttachedTo(int p) {
  this->attach(p);
}
void SimpleLED::setActiveLow() {
  onState = LOW;
}
void SimpleLED::setActiveHigh() {
  onState = HIGH;
}
void SimpleLED::setActive(boolean b) {
  onState = b;
}
void SimpleLED::on() {
  digitalWrite(pin, onState);
}
void SimpleLED::turnOn() {
  this->on();
}
void SimpleLED::set(int on) {
  this->setBrightness(on);
}
void SimpleLED::off() {
  digitalWrite(pin, !onState);
}
void SimpleLED::turnOff() {
  this->off();
}
void SimpleLED::set(boolean state) {
  digitalWrite(pin, state);
}
void SimpleLED::setBrightness(int pwm) {
  switch (pin) {
    case 3:
    case 5:
    case 6:
    case 9:
    case 10:
    case 11:
      if (pwm > 255)
        pwm = 255;
      else if (pwm < 0)
        pwm = 0;
      analogWrite(pin, pwm);
      break;
    default:
      if (pwm > 128)
        this->on();
      else this->off();
  }
}




/*******************************************************************************
                                                        DigitalInput class

  A generic digital input.
  Implements boolean == comparison operator override.
 *******************************************************************************/

DigitalInput::DigitalInput() {}
void DigitalInput::attach(int p) {
  this->attach(p, INPUT_PULLUP);
}
void DigitalInput::isAttachedTo(int p) {
  this->attach(p);
}
void DigitalInput::attach(int p, int mode) {
  pin = p;
  pinMode(pin, mode);
}
void DigitalInput::isAttachedTo(int p, int mode) {
  this->attach(p, mode);
}
int DigitalInput::read() {
  return digitalRead(pin);
}
boolean DigitalInput::operator == (boolean b) {
  return this->read() == b;
}




/*******************************************************************************
                                                        AnalogInput class

  A generic analog input class.
  Overrides boolean comparison operators
 *******************************************************************************/

AnalogInput::AnalogInput() {}
void AnalogInput::attach(int p) {
  pin = p;
  pinMode(pin, INPUT);
}
void AnalogInput::isAttachedTo(int p) {
  this->attach(p);
}
int AnalogInput::read() {
  return analogRead(pin);
}

boolean AnalogInput::operator == (int x) {
  return this->read() == x;
}
boolean AnalogInput::operator >= (int x) {
  return this->read() >= x;
}
boolean AnalogInput::operator <= (int x) {
  return this->read() <= x;
}
boolean AnalogInput::operator > (int x) {
  return this->read() > x;
}
boolean AnalogInput::operator < (int x) {
  return this->read() < x;
}
boolean AnalogInput::operator != (int x) {
  return this->read() != x;
}
