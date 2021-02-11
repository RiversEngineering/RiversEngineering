#ifndef RIVERSTFLUNA_H
#define RIVERSTFLUNA_H

#include <Wire.h>
#include <TFLI2C.h>
#define ADDRESS 0x10


class TFLuna {
private:
  TFLI2C tflI2C;
  int address = ADDRESS;
public:
  TFLuna();
  void begin();
  int read();
};

#endif
