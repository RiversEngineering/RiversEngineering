#include "RiversColorSensor.h"

ColorSensor::ColorSensor(tcs34725IntegrationTime_t time, tcs34725Gain_t gain) {
  tcs = new Adafruit_TCS34725(time, gain);
}
void ColorSensor::begin() {
  tcs->begin();
}
Color ColorSensor::readRGBC() {
  tcs->getRawData(&color.R, &color.G, &color.B, &color.C);
  float x = (float)color.R / (float)color.C;
  color.R = pow(x, GAMMA) * 255;
  x = color.G / (float)color.C;
  color.G = pow(x, GAMMA) * 255;
  x = color.B / (float)color.C;
  color.B = pow(x, GAMMA) * 255;
  return color;
}
Color ColorSensor::readRGB() {
  this->readRGBC();
}
int ColorSensor::read() {
  return this->readClear();
}
int ColorSensor::readRed() {
  return this->readRGBC().R;
}
int ColorSensor::readGreen() {
  return this->readRGBC().G;
}
int ColorSensor::readBlue() {
  return this->readRGBC().B;
}
int ColorSensor::readClear() {
  return this->readRGBC().C;
}
int ColorSensor::getRed() {
  return color.R;
}
int ColorSensor::getGreen() {
  return color.G;
}
int ColorSensor::getBlue() {
  return color.B;
}
int ColorSensor::getClear() {
  return color.C;
}
Color ColorSensor::getColor() {
  return color;
}
