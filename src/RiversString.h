#ifndef RIVERS_STRING_H
#define RIVERS_STRING_H

#include <Arduino.h>
#include <String.h>

class RString {
  private:
    char* c;
    int n;

  public:
    RString();
    void operator = (String str);
    void operator = (char a);
    void addChar(char a);
    void operator += (char a);
    void operator += (int x);
    char operator [] (int i);
    boolean equals(RString r);
    boolean operator == (RString r);
    boolean operator != (RString r);
    int length();

    void print(HardwareSerial* serial);
    void println(HardwareSerial* serial);
};


#endif
