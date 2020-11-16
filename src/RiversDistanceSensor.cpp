#include "RiversDistanceSensor.h"

#ifdef USE_ADAFRUIT


//Adafruit Variant
DistanceSensor::DistanceSensor() {
}
void DistanceSensor::begin(Adafruit_VL53L0X::VL53L0X_Sense_config_t config_t) {
  tof.begin(config_t);
}
double DistanceSensor::read() {
  tof.rangingTest(&measure, false);
  if (measure.RangeStatus != 4) {
    return measure.RangeMilliMeter / conversionFactor;
  }
  else return -1;
}
void DistanceSensor::setConversionFactor(double cf) {
  conversionFactor = cf;
}
void DistanceSensor::mm() {
  this->setConversionFactor(1);
}
void DistanceSensor::cm() {
  this->setConversionFactor(10);
}
void DistanceSensor::m() {
  this->setConversionFactor(1000);
}
void DistanceSensor::in() {
  this->setConversionFactor(25.4);
}
void DistanceSensor::ft() {
  this->setConversionFactor(12 * 25.4);
}



#else

//DF Robot Variant

DistanceSensor::DistanceSensor() {
  tof = new DFRobotVL53L0X;
}
void DistanceSensor::attach(int i) {}
void DistanceSensor::isAttachedTo(int i) {}
void DistanceSensor::begin() {
  Wire.begin();
  tof->begin(0x50);
  tof->setMode(Continuous, High);
  tof->start();
}
double DistanceSensor::read() {
  return tof->getDistance() / conversionFactor;
}
void DistanceSensor::setConversionFactor(double cf) {
  conversionFactor = cf;
}
void DistanceSensor::mm() {
  this->setConversionFactor(1);
}
void DistanceSensor::cm() {
  this->setConversionFactor(10);
}
void DistanceSensor::m() {
  this->setConversionFactor(1000);
}
void DistanceSensor::in() {
  this->setConversionFactor(25.4);
}
void DistanceSensor::ft() {
  this->setConversionFactor(12 * 25.4);
}
#endif
