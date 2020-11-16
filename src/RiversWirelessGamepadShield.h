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
    WirelessGamepadShield();
    void begin(int baud = BAUD);
    void transmit();
    void setDelay(int d);
  private:
    int _delay = 60;
    int _xOffset = 0;
    int _yOffset = 0;
};

#endif
