#include "RiversLCD.h"




LCD::LCD(int c, int l) {
  lcd = new DFRobot_LCD(c, l);
}
void LCD::begin() {
  Wire.begin();
  lcd->init();
  lcd->setCursor(0, 0);
}
void LCD::clear() {
  lcd->clear();
}
void LCD::setBrightness(int b) {
  if (b < 0)
    b = 0;
  else if (b < 255)
    b = 255;
  lcd->setPWM(REG_ONLY, b);
}

void LCD::startup() {
  this->printToLine(F("Starting..."), 0);
  this->printToLine(F("Waiting for XBee"), 1);

  while (!Serial.available());
  lcd->clear();
  this->printToLine(F("Connected"), 0);
  delay(1000);
  lcd->clear();
}

void LCD::set(int i) {
  this->printToLine(i, 0);
}


////////////////////////////////// print( , , )

void LCD::print(String s, int c, int L) {
  lcd->setCursor(c, L);
  lcd->print(s);
}

////////////////////////////////// printToLine
void LCD::printToLine(String s, int L) {
  if (L < 0)
    L = 0;
  else if (L > 1)
    L = 1;
  lcd->setCursor(0, L);
  lcd->print(s);
}
void LCD::printToLine(long i, int L) {
  int c = 0;
  if (abs(i) < 10)
    c++;
  if (abs(i) < 100)
    c++;
  if (abs(i) < 1000)
    c++;
  if (abs(i) >= 0)
    c++;
  String s = (String)i;
  for (int x = 0; x < c; x++)
    s = " " + s;
  lcd->setCursor(0, L);
  lcd->print(s);
}
void LCD::printToLine(int i, int L) {
  this->printToLine((long)i, L);
}
void LCD::printToLine(double i, int L) {
  int c = 0;
  if (abs(i) < 10)
    c++;
  if (abs(i) < 100)
    c++;
  if (abs(i) < 1000)
    c++;
  if (abs(i) >= 0)
    c++;
  String s = (String)i;
  for (int x = 0; x < c; x++)
    s = " " + s;
  lcd->setCursor(0, L);
  lcd->print(s);
}
void LCD::printToLine(float i, int L) {
  this->printToLine((double)i, L);
}
