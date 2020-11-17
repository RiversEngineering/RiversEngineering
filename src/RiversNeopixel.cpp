#include "RiversNeopixel.h"

Neopixel::Neopixel() {}
void Neopixel::attach(int p, int n) {
  pix = Adafruit_NeoPixel(n, p, NEO_GRB + NEO_KHZ800);
  numPix = n;
  pin = p;
  pix.begin();
}
void Neopixel::isAttachedTo(int p) {
  pin = p;
}
void Neopixel::setNumPixels(int n) {
  numPix = n;
}
void Neopixel::begin() {
  pix = Adafruit_NeoPixel(numPix, pin, NEO_GRB + NEO_KHZ800);
  pix.begin();
}
void Neopixel::setPixel(int p, int r, int g, int b) {
  pix.setPixelColor(p, r, g, b);
}
void Neopixel::setAllPixels(int r, int g, int b) {
  for (int i = 0; i < numPix; i++) {
    pix.setPixelColor(i, r, g, b);
  }
}
void Neopixel::preparePixel(int p, int r, int g, int b) {
  this->setPixel(p, r, g, b);
}
void Neopixel::prepareAllPixels(int r, int g, int b) {
  this->setAllPixels(r, g, b);
}
void Neopixel::show() {
  pix.show();
}
int Neopixel::numberOfPixels() {
  return numPix;
}
void Neopixel::set(int r, int g, int b) {
  this->setAllPixels(r, g, b);
  this->show();
}




LED::LED() {}
void LED::attach(int p) {
  pix = Adafruit_NeoPixel(1, p, NEO_GRB + NEO_KHZ800);
  numPix = 1;
  pin = p;
  pix.begin();
}
void LED::isAttachedTo(int p) {
  this->attach(p);
}
void LED::set(int r, int g, int b) {
  pix.setPixelColor(0, r, g, b);
  pix.show();
}
void LED::setColor(int r, int g, int b) {
  R = r;
  G = g;
  B = b;
  pix.setPixelColor(0, r, g, b);
  pix.show();
}
