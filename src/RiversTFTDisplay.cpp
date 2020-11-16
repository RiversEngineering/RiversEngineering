#include "RiversTFTDisplay.h"

Display::Display() {
}


void Display::begin() {
  tft.begin();
  tft.setRotation(3);
  touch.begin();
  touch.setRotation(1);
  analogWrite(A0, 128);
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

void Display::println(String s, int x, int y, uint16_t color) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.println(s);
}
void Display::println(int s, int x, int y, uint16_t color) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.println(s);
}
void Display::println(float s, int x, int y, uint16_t color) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.println(s);
}
void Display::println(long s, int x, int y, uint16_t color) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.println(s);
}

void Display::println(String s, int x, int y, int r, int g, int b) {
  this->println(s, x, y, this->color(r, g, b));
}
void Display::println(int s, int x, int y, int r, int g, int b) {
  this->println(s, x, y, this->color(r, g, b));
}
void Display::println(float s, int x, int y, int r, int g, int b) {
  this->println(s, x, y, this->color(r, g, b));
}
void Display::println(long s, int x, int y, int r, int g, int b) {
  this->println(s, x, y, this->color(r, g, b));
}

void Display::println(String s, int li, int r, int g, int b) {
  this->println(s, 0, li * textSize * 8, this->color(r, g, b));
}
void Display::println(int s, int li, int r, int g, int b) {
  this->println(s, 0, li * textSize * 8, this->color(r, g, b));
}
void Display::println(float s, int li, int r, int g, int b) {
  this->println(s, 0, li * textSize * 8, this->color(r, g, b));
}
void Display::println(long s, int li, int r, int g, int b) {
  this->println(s, 0, li * textSize * 8, this->color(r, g, b));
}


boolean Display::touchDraw(int r,  int g, int b, int pen) {
  return this->touchDraw(this->color(r, g, b));
}
boolean Display::touchDraw(uint16_t color, int pen) {
  if (touch.touched()) {
    TouchPoint p = this->getTouchPoint();
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    tft.fillCircle(p.x, p.y, pen, color);
    return true;
  }
  return false;
}


void Display::drawPixel(int x, int y, int r, int g, int b) {
  tft.writePixel(x, y, this->color(r, g, b));
}

void Display::drawLine(int x0, int y0, int x1, int y1, int r, int g, int b) {
  tft.drawLine(x0, y0, x1, y1, this->color(r, g, b));
}


void Display::drawRect(int x, int y, int w, int h, int r, int g, int b) {
  tft.drawRect(x, y, w, h, this->color(r, g, b));
}
void Display::fillRect(int x, int y, int w, int h, int r, int g, int b) {
  tft.fillRect(x, y, w, h, this->color(r, g, b));
}
void Display::drawRoundRect(int x, int y, int w, int h, int rad, int r, int g, int b) {
   tft.drawRoundRect(x, y, w, h, rad, this->color(r, g, b));
}
void Display::fillRoundRect(int x, int y, int w, int h, int rad, int r, int g, int b) {
  tft.fillRoundRect(x, y, w, h, rad, this->color(r, g, b));
}

void Display::drawCircle(int x, int y, int rad, int r, int g, int b) {
  tft.drawCircle(x, y, rad, this->color(r, g, b));
}
void Display::fillCircle(int x, int y, int rad, int r, int g, int b) {
  tft.fillCircle(x, y, rad, this->color(r, g, b));
}

void Display::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int r, int g, int b) {
  tft.drawTriangle(x0, y0, x1, y1, x2, y2, this->color(r, g, b));
}
void Display::fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int r, int g, int b) {
  tft.fillTriangle(x0, y0, x1, y1, x2, y2, this->color(r, g, b));
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
