/////////////////////////////////////////////////// Rivers Engineering Library
#include "src/RiversTFTDisplay.h"

Display tft;


/////////////////////////////////////////////////// setup()
void setup() {

  Serial.begin(115200);
  tft.begin();
  tft.clearScreen();
  tft.setTextColor(TFT_RED);
  tft.setTextSize(3);
  tft.printToLine("Testing", 1);
  tft.printToLine("Test 2", 3);
  tft.printToLine("Test 3", 2);
  tft.setDrawColor(TFT_GREEN);
  tft.fillTriangle(100, 100, 100, 200, 200, 200);
}



/////////////////////////////////////////////////// loop()
void loop() {
  
  
}
