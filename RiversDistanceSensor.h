/*****************************************************

   VL53L0X ToF Distance Sensor Library
   Yoshiro Fujita, 2019
   For use in The Rivers School Engineering program

   Implements a class that serves as a wrapper around
   the DFRobot VL53L0X library. This simplifies the use
   for students and implements methods consistent with
   other Rivers libraries.

   Requires that the DFRobot VL53L0X library be installed

 *****************************************************/
#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H


// use the adafruit variant
#define USE_ADAFRUIT


#include "RiversIO.h"
#include "Wire.h"


#ifndef I2C
#define I2C 0
#endif

#ifdef USE_ADAFRUIT
#include "Adafruit_VL53L0X.h"

#define LONG_RANGE Adafruit_VL53L0X::VL53L0X_SENSE_LONG_RANGE
#define DEFAULT_RANGE Adafruit_VL53L0X::VL53L0X_SENSE_DEFAULT
#define HIGH_SPEED Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_SPEED
#define HIGH_ACCURACY Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY



#else
#include "DFRobot_VL53L0X.h"
#endif

class DistanceSensor : public Input {
  private:
    double conversionFactor = 1;
#ifdef USE_ADAFRUIT
    Adafruit_VL53L0X tof;
    VL53L0X_RangingMeasurementData_t measure;
#else
    DFRobotVL53L0X* tof;
#endif

  public:
    DistanceSensor();
    void begin(Adafruit_VL53L0X::VL53L0X_Sense_config_t config_t = LONG_RANGE);
    double read();
    void setConversionFactor(double cf);
    void mm();
    void cm();
    void m();
    void in();
    void ft();
};

#endif
