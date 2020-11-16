/*****************************************************

   Rivers Wireless Gamepad Library
   Yoshiro Fujita, 2019
   For use in The Rivers School Engineering program

   Implements a class to transmit data from the DFRobot
   Wireless Gamepad. Intended for use with paired XBee
   devices, allowing the gamepad to control a robot.

 *****************************************************/
#ifndef WIRELESS_GAMEPAD_H
#define WIRELESS_GAMEPAD_H

#include "RiversString.h"
#include "RiversWirelessProtocol.h"

//#define UPDATE_ONLY

#define BAUD 115200

//DFRobot wireless gamepad pinout
//Joystick Axes
#define LEFTX_PIN A5
#define LEFTY_PIN A4
#define RIGHTX_PIN A3
#define RIGHTY_PIN A2

//Joystick buttons
#define B_LEFTSTICK_PIN A0
#define B_RIGHTSTICK_PIN A1

//Buttons
#define B1_PIN 9
#define B2_PIN 11
#define B3_PIN 12
#define B4_PIN 10

//Shoulder Buttons
#define L1_PIN 15
#define L2_PIN 16
#define R1_PIN 13
#define R2_PIN 14

//Dpad
#define UP_PIN 5
#define DOWN_PIN 7
#define LEFT_PIN 6
#define RIGHT_PIN 8

//Other
#define VIBRATION_PIN 2
#define LED_PIN 17
#define START_PIN 4
#define SELECT_PIN 3



/*******************************************************************************
                                                        WirelessGamepad class

  For use with the DFRobot Wireless Gamepad. Implements the wireless protocol
  used here on the sending side, allowing for easy teleop of robot.

  Sends a new packet every 60 ms (about as fast as could work reliably in tests)
 *******************************************************************************/
class WirelessGamepad {
  public:
    WirelessGamepad();
    void begin(int baud = BAUD);
    void transmit();
    void setDelay(int d);
  private:
    int _delay = 60;
    int _xLOffset = 0;
    int _xROffset = 0;
    int _yLOffset = 0;
    int _yROffset = 0;
    RString previous;
    RString current;
};

#endif
