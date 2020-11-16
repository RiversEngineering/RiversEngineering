/*****************************************************
 * 
 * Rivers Wireless Gamepad Shield Library
 * Yoshiro Fujita, 2019
 * For use in The Rivers School Engineering program
 * 
 * Implements a class to transmit data from the DFRobot
 * Gamepad Shield. Intended for use with paired XBee
 * devices, allowing the shield to control a robot.
 * 
 *****************************************************/
 #ifndef WIRELESS_GAMEPAD_SHIELD_H
#define WIRELESS_GAMEPAD_SHIELD_H

#include <Arduino.h>
#include "RiversWirelessProtocol.h"

#define BAUD 115200

//DFRobot input shield pinout
//Joystick Axes
#define LEFTX_PIN A3
#define LEFTY_PIN A2

//Joystick buttons
#define B_LEFTSTICK_PIN A0

//Buttons
#define B1_PIN 8
#define B2_PIN 12
#define B3_PIN A1
#define B4_PIN 9

/*******************************************************************************
                                                        Wirelessgamepad class

  For use with the DFRobot Input Shield, attached to an Arduino Uno. 
  Implements the wireless protocol used here on the sending side, allowing for 
  easy teleop of robot. 
  
  Sends a new packet every 60 ms (about as fast as could work reliably in tests)
  *****************************************************************************/

class WirelessGamepadShield {
  public:
    WirelessGamepadShield() {
    };
    void begin(int baud = BAUD) {
      Serial.begin(baud);

      pinMode(LEFTX_PIN, INPUT);
      pinMode(LEFTY_PIN, INPUT);

      //Joystick button
      pinMode(B_LEFTSTICK_PIN, INPUT);

      //Buttons
      pinMode(B1_PIN, INPUT);
      pinMode(B2_PIN, INPUT);
      pinMode(B3_PIN, INPUT);
      pinMode(B4_PIN, INPUT);

      //calibrate stick
      for (int i = 0; i < 10; i++)
      {
        _xOffset += analogRead(LEFTX_PIN);
        _yOffset += analogRead(LEFTY_PIN);
      }

      _xOffset /= 10;
      _yOffset /= 10;

      _xOffset = 511 - _xOffset;
      _yOffset = 511 - _yOffset;
    };
    void transmit() {
      long now;
      long start = millis();
      int remainingDelay = 0;
      String packet = "";

      packet += LEFT_X;
      packet += map(analogRead(LEFTX_PIN) + _xOffset, 0, 1023, 255, -255);
      packet += LEFT_Y;
      packet += -map(analogRead(LEFTY_PIN) + _yOffset, 0, 1023, -255, 255);

      packet += BUTTON_1;
      if (!digitalRead(B1_PIN))
        packet += '1';
      else packet += '0';
      packet += BUTTON_2;
      if (!digitalRead(B2_PIN))
        packet += '1';
      else packet += '0';
      packet += BUTTON_3;
      if (!digitalRead(B3_PIN))
        packet += '1';
      else packet += '0';
      packet += BUTTON_4;
      if (!digitalRead(B4_PIN))
        packet += '1';
      else packet += '0';


      packet += BUTTON_LJOY;
      if (!digitalRead(B_LEFTSTICK_PIN))
        packet += '1';
      else packet += '0';

      Serial.println(packet);

      delay(_delay);
    };

    void setDelay(int d) {
      _delay = d;
    };
  private:
    int _delay = 60;
    int _xOffset = 0;
    int _yOffset = 0;
};

#endif
