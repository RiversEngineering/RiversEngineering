/////////////////////////////////////////////////// Rivers Engineering Library
#include "src/RiversEngineering.h"

Display screen;



/////////////////////////////////////////////////// setup()
void setup() {

  Serial.begin(115200);
  while (!Serial);
  screen.begin();
  screen.clearScreen();
  screen.setTextColor(TFT_WHITE);
  screen.print("Test", 100, 100);

}



/////////////////////////////////////////////////// loop()
void loop() {
}
