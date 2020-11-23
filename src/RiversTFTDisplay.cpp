#include "RiversTFTDisplay.h"

Display::Display() {
}


void Display::begin() {
  analogWrite(A0, 1000);
  tft.begin();
  tft.setRotation(3);
  touch.begin();
  touch.setRotation(1);
}

boolean Display::touched() {
  return touch.touched();
}

TouchPoint Display::getTouchPoint() {
  return touch.getPoint();
}

void Display::clearScreen() {

  tft.fillScreen(ILI9341_BLACK);
}


void Display::setTextSize(uint8_t size) {
  textSize = size;
}

void Display::setTextColor(uint16_t color){
  textColor = color;
}
void Display::setTextColor(int r, int g, int b) {
  this->setTextColor(this->color(r, g, b));
}


void Display::print(String s, int x, int y) {
  tft.setCursor(x, y);
  tft.setTextColor(textColor);
  tft.setTextSize(textSize);
  tft.println(s);
}
void Display::print(int s, int x, int y) {
  tft.setCursor(x, y);
  tft.setTextColor(textColor);
  tft.setTextSize(textSize);
  tft.println(s);
}
void Display::print(float s, int x, int y) {
  tft.setCursor(x, y);
  tft.setTextColor(textColor);
  tft.setTextSize(textSize);
  tft.println(s);
}
void Display::print(long s, int x, int y) {
  tft.setCursor(x, y);
  tft.setTextColor(textColor);
  tft.setTextSize(textSize);
  tft.println(s);
}

void Display::printToLine(String s, int li) {
  this->print(s, 0, li * textSize * 8);
}
void Display::printToLine(int s, int li) {
  this->print(s, 0, li * textSize * 8);
}
void Display::printToLine(float s, int li) {
  this->print(s, 0, li * textSize * 8);
}
void Display::printToLine(long s, int li) {
  this->print(s, 0, li * textSize * 8);
}



void Display::setDrawColor(uint16_t color) {
  drawColor = color;
}
void Display::setDrawColor(int r, int g, int b) {
  this->setDrawColor(this->color(r,g,b));
}


boolean Display::touchDraw(int pen) {
  if (touch.touched()) {
    TouchPoint p = this->getTouchPoint();
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    tft.fillCircle(p.x, p.y, pen, drawColor);
    return true;
  }
  return false;
}


void Display::drawPixel(int x, int y) {
  tft.writePixel(x, y, drawColor);
}

void Display::drawLine(int x0, int y0, int x1, int y1) {
  tft.drawLine(x0, y0, x1, y1, drawColor);
}


void Display::drawRect(int x, int y, int w, int h) {
  tft.drawRect(x, y, w, h, drawColor);
}
void Display::fillRect(int x, int y, int w, int h) {
  tft.fillRect(x, y, w, h, drawColor);
}
void Display::drawRoundRect(int x, int y, int w, int h, int rad) {
   tft.drawRoundRect(x, y, w, h, rad, drawColor);
}
void Display::fillRoundRect(int x, int y, int w, int h, int rad) {
  tft.fillRoundRect(x, y, w, h, rad, drawColor);
}

void Display::drawCircle(int x, int y, int rad) {
  tft.drawCircle(x, y, rad, drawColor);
}
void Display::fillCircle(int x, int y, int rad) {
  tft.fillCircle(x, y, rad, drawColor);
}

void Display::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2) {
  tft.drawTriangle(x0, y0, x1, y1, x2, y2, drawColor);
}
void Display::fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2) {
  tft.fillTriangle(x0, y0, x1, y1, x2, y2, drawColor);
}


void Display::setBrightness(uint16_t bright) {
  if (bright > 1023)
    bright = 1023;

  analogWrite(A0, bright);
}


uint16_t Display::color(int r, int g, int b) {
  return (uint8_t)map(r, 0, 255, 0, 31) << 11
         | (uint8_t)map(g, 0, 255, 0, 63) << 5
         | (uint8_t)map(b, 0, 255, 0, 31);
}

Adafruit_ILI9341 Display::display() {
  return this->tft;
}

XPT2046_Touchscreen Display::touchScreen() {
  return this->touch;
}
