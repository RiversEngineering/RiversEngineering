#ifndef RIVERS_NEOPIXEL_H
#define RIVERS_NEOPIXEL_H

#include "RiversIO.h"

#define RGB_RED 20, 0, 0
#define RGB_ORANGE 10, 15, 0
#define RGB_YELLOW 5, 15, 0
#define RGB_GREEN 0, 20, 0
#define RGB_CYAN 0, 10, 10
#define RGB_BLUE 0, 0, 20
#define RGB_PURPLE 10, 0, 15
#define RGB_WHITE 10, 10, 10
#define RGB_OFF 0, 0, 0



/*******************************************************************************
                                                        New Neopixel class
 *******************************************************************************/

class Neopixel : public Output {
  private:
    Adafruit_NeoPixel pix;
    int numPix = 8;
    int pin = 3;

  public:
    Neopixel() {}
    void attach(int p, int n) {
      pix = Adafruit_NeoPixel(n, p, NEO_GRB + NEO_KHZ800);
      numPix = n;
      pin = p;
      pix.begin();
    }
    void isAttachedTo(int p) {
      pin = p;
    }
    void setNumPixels(int n) {
      numPix = n;
    }
    void begin() {
      pix = Adafruit_NeoPixel(numPix, pin, NEO_GRB + NEO_KHZ800);
      pix.begin();
    }
    void setPixel(int p, int r, int g, int b) {
      pix.setPixelColor(p, r, g, b);
    }
    void setAllPixels(int r, int g, int b) {
      for (int i = 0; i < numPix; i++) {
        pix.setPixelColor(i, r, g, b);
      }
    }
    void preparePixel(int p, int r, int g, int b) {
      this->setPixel(p, r, g, b);
    }
    void prepareAllPixels(int r, int g, int b) {
      this->setAllPixels(r, g, b);
    }
    void updatePixels() {
      pix.show();
    }
    void show() {
      this->updatePixels();
    }
    void sendToPixels() {
      this->updatePixels();
    }
    int numberOfPixels() {
      return numPix;
    }
    void set(int r, int g, int b) {
      this->setAllPixels(r, g, b);
      this->updatePixels();
    }
};

#endif
