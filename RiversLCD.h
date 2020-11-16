/*****************************************************
 * 
 * DFRobot 2 Line LCD Library
 * Yoshiro Fujita, 2019
 * For use in The Rivers School Engineering program
 * 
 * Implements a class that serves as a wrapper around
 * the DFRobot LCD library. This simplifies the use
 * for students and implements methods consistent with
 * other Rivers libraries.
 * 
 * Requires that the DFRobot LCD library be installed.
 * 
 *****************************************************/
#ifndef LCD_H
#define LCD_H

#include <Wire.h>
#include <DFRobot_LCD.h>
#include "RiversIO.h"

#ifndef I2C
#define I2C 0
#endif

#define LCD_PRINTTOLINE(x) \
  void printToLine(x i, int L) { \
    this->printToLine((String)i, L); \
  }

#define LCD_PRINT(x) \
  void print(x i, int c, int L) { \
    lcd->setCursor(c, L); \
    lcd->print((String)i); \
  }

#define LCD_PRINT2(x) \
  void print(x s) { \
    this->printToLine(s, 0); \
  }

#define LCD_CLEARPRINTTOLINE(x) \
  void clearPrintToLine(x s, int L) { \
    lcd->clear(); \
    this->printToLine(s, L); \
  }

#define LCD_CLEARPRINT(x) \
  void clearPrint(x s) { \
    lcd->clear(); \
    this->printToLine(s, 0); \
  }



class LCD : public Output {
  public:
    DFRobot_LCD* lcd;

    LCD(int c = 16, int l = 2);
    void begin();
    void clear();
    void setBrightness(int b);

    void startup();

    void set(int i);


    ////////////////////////////////// print( , , )

    void print(String s, int c, int L);
    LCD_PRINT(int)
    LCD_PRINT(long)
    LCD_PRINT(float)
    LCD_PRINT(double)
    LCD_PRINT(char *)



    ////////////////////////////////// printToLine
    void printToLine(String s, int L);
    void printToLine(long i, int L);
    void printToLine(int i, int L);
    void printToLine(double i, int L);
    void printToLine(float i, int L);
    LCD_PRINTTOLINE(char *)


    
    ////////////////////////////////// print
    LCD_PRINT2(String)
    LCD_PRINT2(int)
    LCD_PRINT2(float)
    LCD_PRINT2(long)
    LCD_PRINT2(double)
    LCD_PRINT2(char *)

    ////////////////////////////////// clearPrintToLine
    LCD_CLEARPRINTTOLINE(String)
    LCD_CLEARPRINTTOLINE(int)
    LCD_CLEARPRINTTOLINE(float)
    LCD_CLEARPRINTTOLINE(long)
    LCD_CLEARPRINTTOLINE(double)
    LCD_CLEARPRINTTOLINE(char *)

    ////////////////////////////////// clearPrint
    LCD_CLEARPRINT(String)
    LCD_CLEARPRINT(int)
    LCD_CLEARPRINT(float)
    LCD_CLEARPRINT(long)
    LCD_CLEARPRINT(double)
    LCD_CLEARPRINT(char *)
};



#endif
