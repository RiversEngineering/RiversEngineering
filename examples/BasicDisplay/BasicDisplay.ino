/*  Basic Screen
 *  Fuj, 2020
 *  
 *  This program shows the basic usage of the TFT LCD screen
 */
#include <RiversEngineering.h>

Display screen;

int drawColor = 200;

void setup() {
  screen.begin();
  
  screen.clearScreen();
  screen.setTextColor(TFT_WHITE);
  screen.print("Hello!");
  
  delay(2000);

  screen.clearScreen();
  screen.setTextSize(3);
  screen.setTextColor(TFT_RED);
  screen.printToLine("RIVERS!", 3);

  delay(2000);
  
  screen.clearScreen();
  for (int radius = 200; radius > 20; radius -= 10) {
    drawColor -= 8;
    screen.setDrawColor(drawColor, 0, 0);
    screen.fillCircle(160, 120, radius);
  }
}


void loop() {
  
}
