/*****************************************************
 * 
 * Rivers Serial Monitor Wrapper Library
 * Yoshiro Fujita, 2019
 * For use in The Rivers School Engineering program
 * 
 * Implements a series of functions to make use of the
 * Serial Monitor slightly simpler and more intuitive
 * for beginning students unfamiliar with OOP.
 * 
 * Still in development.
 * 
 *****************************************************/
#ifndef SERIALWRAPPER_H
#define SERIALWRAPPER_H

#define SERIAL_PRINTLN(x) \
  void println(x s) { \
    Serial.println(s); \
  }

SERIAL_PRINTLN(String)
SERIAL_PRINTLN(int)
SERIAL_PRINTLN(float)
SERIAL_PRINTLN(long)
SERIAL_PRINTLN(double)
SERIAL_PRINTLN(char*)
SERIAL_PRINTLN(char)


#define SERIAL_PRINT(x) \
  void print(x s) { \
    Serial.print(s); \
  }

SERIAL_PRINT(String)
SERIAL_PRINT(int)
SERIAL_PRINT(float)
SERIAL_PRINT(long)
SERIAL_PRINT(double)
SERIAL_PRINT(char*)
SERIAL_PRINT(char)


void printTab() {
  Serial.print("\t");
}

void startSerialMonitor(int b = 9600) {
  Serial.begin(b);
}

#endif
