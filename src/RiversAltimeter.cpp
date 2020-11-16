#include "RiversAltimeter.h"

Altimeter::Altimeter() {}
double Altimeter::calculateSeaLevelPressure(double altitude) {
  double seaP = this->readPressure() / pow(1 - (altitude / 44330), 5.255);
  return seaP;
}
void Altimeter::setTempOversample(int x) {
  tempOversample = x;
}
void Altimeter::setPressureOversample(int x) {
  pressureOversample = x;
}
void Altimeter::setIIRCoefficient(int x) {
  IIRCoeff = x;
}
void Altimeter::begin(float altitude = 54.0) {
  altimeter = new Adafruit_BMP3XX;
  altimeter->begin_I2C();
  altimeter->setTemperatureOversampling(tempOversample);
  altimeter->setPressureOversampling(pressureOversample);
  altimeter->setIIRFilterCoeff(IIRCoeff);
  seaLevelPressure = this->calculateSeaLevelPressure(altitude);
}

float Altimeter::readAltitude() {
  return altimeter->readAltitude(seaLevelPressure / 100);
}
float Altimeter::readPressure() {
  return altimeter->readPressure();
}
float Altimeter::readTemperature() {
  return altimeter->readTemperature();
}
