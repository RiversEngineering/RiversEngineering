#include "RiversTime.h"

Stopwatch::Stopwatch() {};
void Stopwatch::start() {
  startTime = millis();
}
void Stopwatch::reset() {
  this->start();
}
void Stopwatch::restart() {
  this->start();
}
long Stopwatch::elapsedMillis() {
  return (millis() - startTime);
}
double Stopwatch::elapsedSeconds() {
  return this->elapsedMillis() / 1000.0;
}
int Stopwatch::read() {
  return elapsedMillis();
}





Timer::Timer() {}
Timer::Timer(long length) {
  this->setLength(length);
}
Timer::Timer(int length) {
  this->setLength(length);
}
void Timer::set(long length) {
  this->setLength(length);
}
void Timer::setLength(long length) {
  waitTime = length;
}
void Timer::start() {
  startTime = millis();
}
boolean Timer::isDone() {
  return (millis() > startTime + waitTime);
}
int Timer::read() {
  return this->isDone();
}
