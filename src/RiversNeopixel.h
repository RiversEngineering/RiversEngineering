#ifndef RIVERS_NEOPIXEL_H
#define RIVERS_NEOPIXEL_H

#include "RiversIO.h"
#include "Adafruit_NeoPixel.h"

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
    Neopixel();
    void attach(int p, int n);
    void attach(int p);
    void isAttachedTo(int p);
    void setNumPixels(int n);
    void begin();
    void setPixel(int p, int r, int g, int b);
    void setAllPixels(int r, int g, int b);
    void preparePixel(int p, int r, int g, int b);
    void prepareAllPixels(int r, int g, int b);
    void show();
    int numberOfPixels();
    void set(int r, int g, int b);
};


class LED : public Output {
  private:
    Adafruit_NeoPixel pix;
    int numPix = 1;
    int pin = 3;
    int R = 100;
    int G = 0;
    int B = 0;

  public:
    LED();
    void attach(int p);
    void isAttachedTo(int p);
    void set(int r, int g, int b);
    void setColor(int r, int g, int b);
};

#endif
