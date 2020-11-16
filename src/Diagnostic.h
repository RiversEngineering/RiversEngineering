#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H


#include "RiversEngineering.h"


#define PLN Serial.println
#define P Serial.print

boolean dontStop = true;
String str;


void runDiagnostic() {
  Serial.begin(9600);

  while (dontStop) {

    printMenu();
    str = waitForInput();
    PLN(str);
    parseInput(str);
  }
}



void printMenu() {
  /*
     Inputs
     button           bu
     pot              pot
     light            li
     tof              tof
     ultrasonic       ult
     altimeter        alt
     color            co
     pulse            pu

     Outputs
     Buzzer           bz
     LED              led
     Neopixel         np1
     Neopixel Strip   np
     LCD              lcd
     Servo            s

     Arduino

     Pin Tests
     all digital pins input         di
     all digital pins output        do
     all analog pins input          ai

  */
  PLN("Input Tests:");
  PLN("  Button (bu)");
  PLN("  Potentiometer (pot)");
  PLN("  Light Sensor (li)");
  PLN("  Time of Flight (tof)");
  PLN("  Ultrasonic (ult)");
  PLN("  Altimeter (alt)");
  PLN("  Color Sensor (co)");
  PLN("  Pulse (pu)");
  PLN("  ");
  PLN("Output Tests");
  PLN("  Buzzer (bz)");
  PLN("  LED (led)");
  PLN("  Neopixel, Single (np1)");
  PLN("  Neopixel, Strip (np8)");
  PLN("  LCD (lcd)");
  PLN("  Servo (s)");
  PLN("  ");
  PLN("Arduino Pin Tests:");
  PLN("  All Digital Pins Input (di)");
  PLN("  All Digital Pins Output (do)");
  PLN("  All Analog Pins Input (ai)");
  PLN("");
  P("Select a test to run: ");
}




String waitForInput() {
  while (!Serial.available());

  String s = Serial.readString();

  return s;
}

int waitForInput() {
  while (!Serial.available());

  int i = Serial.parseInt();

  return i;
}




void parseInput(String s) {
  if (s[0] == 'n' && s[1] == 'p') {
    int np = 0;
    for (int i = 2; i < s.length(); i++) {
      np *= 10;
      np += s[i];
    }

    npTest(np);
  }
  else switch (s) {
      case "bu":
        buttonTest();
        break;
      case "pot":
        break;
      case "li":
        break;
      case "tof":
        break;
      case "ult":
        break;
      case "alt":
        break;
      case "co":
        break;
      case "pu":
        break;
      case "bz":
        break;
      case "led":
        break;
      case "lcd":
        break;
      case "s":
        break;
      case "di":
        break;
      case "do":
        break;
      case "ai":
        break;
    }
}


int pinPrompt() {
  P("Enter pin (default 7): ");
  p = waitForInput();
  if (p == 0)
    p = 7;
  PLN(p);
}

int pinPrompt(int d) {
  P("Enter pin (default ");
  P(d);
  P("): ");
  p = waitForInput();
  if (p == 0)
    p = d;
  PLN(p);
}


void buttonTest() {
  int p = 7; 

  p = pinPrompt();

  Button b;
  b.attach(p);
  while (!Serial.available()) {
    if (button.transitionPressed()) 
      PLN("PRESSED!");
    else if (button.transitionReleased())
      PLN("released");
  }
  Serial.flush();
}

void npTest(int np) {
  int p = 7;

  p = pinPrompt();

  Neopixel n;
  n.attach(p);
  n.setNumPixels(np);
  n.begin();

  
  while (!Serial.available()) {
  n.setAllPixels(100, 0, 0);
  delay(500);
  n.setAllPixels(0, 100, 0);
  delay(500);
  n.setAllPixels(0, 0, 100);
  delay(500);
  n.setAllPixels(0, 0, 0);
  delay(500);
  if (np > 1)
    for (int i = 0; i < np; i++) {
      n.setAllPixels(0, 0, 0);
      n.setPixel(i, 100, 0, 0);
      delay(200);
    }
  }
  Serial.flush();
}

#endif
