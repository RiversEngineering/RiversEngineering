#include "RiversDistanceSensor.h"

#ifdef USE_ADAFRUIT


//Adafruit Variant
DistanceSensor::DistanceSensor() {
}
void DistanceSensor::begin() {
  tof.begin();
}
double DistanceSensor::read() {
  tof.rangingTest(&measure, false);
  if (measure.RangeStatus != 4 && measure.RangeMilliMeter < 8000) {
    return measure.RangeMilliMeter / conversionFactor;
  }
  else return -1;
}
int DistanceSensor::ambient() {
  return measure.AmbientRateRtnMegaCps;
}

int DistanceSensor::signal() {
  return measure.SignalRateRtnMegaCps;
}

int DistanceSensor::status() {
  return tof.readRangeStatus();
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
void DistanceSensor::begin() {
  Wire.begin();
  tof->begin(0x50);
  tof->setMode(Continuous, High);
  tof->start();
}
double DistanceSensor::read() {
  return tof->getDistance() / conversionFactor;
}

int DistanceSensor::ambient() {
  return tof->getAmbientCount();
}

int DistanceSensor::signal() {
  return tof->getSignalCount();
}

int DistanceSensor::status() {
  return tof->getStatus();
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
