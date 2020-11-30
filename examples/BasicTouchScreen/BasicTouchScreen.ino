/*  Basic Touchscreen
    Fuj, 2020

    This program shows the basic usage of the touchscreen
*/
#include <RiversEngineering.h>

Display screen;

// size of the box
int minX = 120;
int maxX = 200;
int minY = 100;
int maxY = 140;

// calculate height and width
int height = maxY - minY;
int width = maxX - minX;

TouchPoint touch;

void setup() {
  screen.begin();
  screen.clearScreen();

  // draw a red rectangle
  screen.setDrawColor(TFT_RED);
  screen.fillRect(minX, minY, width, height);
}


void loop() {
  // if the screen is touched... 
  if (screen.touched()) {

    // get the data about where
    touch = screen.getTouchPoint();

    // if the touch was inside the rectangle...
    if (touch.x > minX && touch.x < maxX && touch.y > minY && touch.y < maxY) {
      
      // change the color to blue
      screen.setDrawColor(TFT_BLUE);
      screen.fillRect(minX, minY, width, height);
    }
  }
}
