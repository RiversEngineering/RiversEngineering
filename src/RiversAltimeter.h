/*****************************************************
 *
 * BMP 388 Altimeter Library
 * Yoshiro Fujita, 2019
 * For use in The Rivers School Engineering program
 *
 * Implements a class that serves as a wrapper around
 * the Adafruit BMP3XX library. This simplifies the use
 * for students and implements methods consistent with
 * other Rivers libraries.
 *
 * Requires that the Adafruit Unified Sensor and
 * BMP3XX libraries be installed.
 *
 *****************************************************/
#ifndef ALTIMETER_H
#define ALTIMETER_H

#include "RiversIO.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

class Altimeter : public Input {
  public:
    Adafruit_BMP3XX* altimeter;
    float seaLevelPressure = 101325;
    int tempOversample = BMP3_OVERSAMPLING_8X;
    int pressureOversample = BMP3_OVERSAMPLING_4X;
    int IIRCoeff = BMP3_IIR_FILTER_COEFF_3;

    Altimeter();
    double calculateSeaLevelPressure(double altitude);
    void setTempOversample(int x);
    void setPressureOversample(int x);
    void setIIRCoefficient(int x);
    void begin(float altitude = 54.0);

    float readAltitude();
    float readPressure();
    float readTemperature();
};
#endif
