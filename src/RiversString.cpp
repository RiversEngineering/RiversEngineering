#include "RiversString.h"

RString::RString() {
  n = 60;
  c = new char[n];
}

int RString::length() {
  return n;
}

void RString::operator = (String str) {
  n = str.length();
  for (int i = 0; i < n; i++) {
    c[i] = str[i];
  }
}

void RString::operator = (char a) {
  n = 1;
  c[0] = a;
}

void RString::addChar(char a) {
  c[n++] = a;
}

void RString::operator += (char a) {
  this->addChar(a);
}

void RString::operator += (int x) {
  char t;
  boolean leadingZeros = true;
  int divisor = 10000;

  if (x < 0) {
    this->addChar('-');
    x *= -1;
  }

  for (int i = 0; i < 5; i++) {
    t = (char)(x / divisor) + '0';

    if (leadingZeros) {
      if (t != '0')
        leadingZeros = false;
    }
    else this->addChar(t);
    x %= divisor;
    divisor /= 10;
  }
}

char RString::operator [] (int i) {
  if (i < n) {
    return c[i];
  }
  else return '?';
}

boolean RString::equals(RString r) {
  if (n != r.length())
    return false;
  for (int i = 0; i < n; i++) {
    if (r[i] != c[i])
      return false;
  }
  return true;
}

boolean RString::operator == (RString r) {
  this->equals(r);
}

boolean RString::operator != (RString r) {
  return !(this->equals(r));
}

void RString::print(HardwareSerial* serial) {
  for (int i = 0; i < n; i++)
    serial->print(c[i]);
}
void RString::println(HardwareSerial* serial) {
  this->print(serial);
  serial->println();
}
