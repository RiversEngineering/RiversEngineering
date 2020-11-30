/*  Basic Neopixel
 *  Fuj, 2020
 *  
 *  This program shows the basic usage of an 8 Neopixel strip
 */
#include <RiversEngineering.h>
#include <RiversNeopixel.h>
Neopixel pixels;


void setup() {
  pixels.isAttachedTo(12);

  // Neopixels use a complex communication, so they need to begin()
  pixels.begin();
}


void loop() {
  // make a rainbow, then pulse, repeat.
  rainbow();
  pulse();
}


// display lots of colors
void rainbow() {
  pixels.preparePixel(0, RGB_RED);
  pixels.preparePixel(1, RGB_ORANGE);
  pixels.preparePixel(2, RGB_YELLOW);
  pixels.preparePixel(3, RGB_GREEN);
  pixels.preparePixel(4, RGB_CYAN);
  pixels.preparePixel(5, RGB_BLUE);
  pixels.preparePixel(6, RGB_PURPLE);
  pixels.preparePixel(7, RGB_WHITE);
  pixels.show();
  delay(1000);
}


// make the neopixels pulse up and down the strip 5x
void pulse() {
  pixels.prepareAllPixels(RGB_OFF);
  delay(200);
  
  for (int i = 0; i < 5; i++) {
    onePulse();
  }
}


// do a single pulse up and down
void onePulse() {
  // pulse up
  for (int i = 0; i <= 7; i++) {
    pixels.preparePixel(i, RGB_RED);
    pixels.show();
    delay(100);
  }
  
  
  // pulse down
  for (int j = 7; j >= 0; j--) {
    pixels.preparePixel(j, RGB_OFF);
    pixels.show();
    delay(100);
  }
}
