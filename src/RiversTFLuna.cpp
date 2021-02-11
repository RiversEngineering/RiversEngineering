#include "RiversTFLuna.h"


TFLuna::TFLuna() {

}
void TFLuna::begin() {
  Wire.begin();

}
int TFLuna::read() {
  int16_t tfDist;
  tflI2C.getData(tfDist, this->address);
  return tfDist;
}
