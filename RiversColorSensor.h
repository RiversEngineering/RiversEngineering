/*****************************************************
 * 
 * TCS34725 RGB Color Sensor Library
 * Yoshiro Fujita, 2019
 * For use in The Rivers School Engineering program
 * 
 * Implements a class that serves as a wrapper around
 * the Adafruit TCS34725 library. This simplifies the use
 * for students and implements methods consistent with
 * other Rivers libraries.
 * 
 * Requires that the Adafruit TCS34725 library be installed
 * 
 *****************************************************/
#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include "RiversIO.h"
#include <Wire.h>
#include "Adafruit_TCS34725.h"


#ifndef GAMMA
#define GAMMA 3
#endif
#ifndef I2C
#define I2C 0
#endif


struct Color {
  uint16_t R, G, B, C;
};

class ColorSensor : public Input {
  private:
    Adafruit_TCS34725* tcs;
    Color color;
  public:
    ColorSensor(tcs34725IntegrationTime_t time = TCS34725_INTEGRATIONTIME_50MS, tcs34725Gain_t gain = TCS34725_GAIN_4X);
    void begin();
    Color readRGBC();
    Color readRGB();
    int read();
    int readRed();
    int readGreen();
    int readBlue();
    int readClear();
    int getRed();
    int getGreen();
    int getBlue();
    int getClear();
    Color getColor();
};

#endif
