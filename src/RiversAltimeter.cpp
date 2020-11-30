#include "RiversAltimeter.h"

Altimeter::Altimeter() {}
double Altimeter::calculateSeaLevelPressure(double altitude) {
  Serial.print("Altitude: ");
  Serial.println(altitude);
  double factor = pow(1 - (altitude / 44330.0), 5.255);
  Serial.println(factor);
  double seaP = this->readPressure() / factor;
  Serial.println(seaP);
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
void Altimeter::begin(float altitude) {
  altimeter = new Adafruit_BMP3XX;
  altimeter->begin_I2C();
  altimeter->setTemperatureOversampling(tempOversample);
  altimeter->setPressureOversampling(pressureOversample);
  altimeter->setIIRFilterCoeff(IIRCoeff);

  this->readPressure();
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
