/*****************************************************
 *
 * Rivers Wireless Input Library
 * Yoshiro Fujita, 2019
 * For use in The Rivers School Engineering program
 *
 * Implements a class to receive data from the DFRobot
 * Wireless Gamepad. Intended for use with paired XBee
 * devices, allowing the gamepad to control a robot.
 *
 *****************************************************/
#ifndef WIRELESS_INPUT_H
#define WIRELESS_INPUT_H

#include <Arduino.h>
#include "RiversWirelessProtocol.h"


//allow for multiple serial ports depending on the board
#ifdef ARDUINO_AVR_LEONARDO
#define SERIAL1
#endif
#ifdef ARDUINO_AVR_MEGA
#define SERIAL1
#define SERIAL23
#endif
#ifdef ARDUINO_AVR_MEGA2560
#define SERIAL1
#define SERIAL23
#endif
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
#define SERIAL1
#endif

#define BAUD 115200

/*******************************************************************************
                                                        WirelessInput class

  Implements the receiving side of the wireless protocol. By default uses Serial,
  but supports Leonardo and Mega boards with multiple Serial ports.
  Calibrates joysticks on startup to find their natural zero point.
  Joysticks operate on ~ +/- 255 scale with this protocol.

  .refresh() must be called regularly (more than every 60 ms, ideally) or the
  robot may begin to experience laggy response times.
 *******************************************************************************/
class WirelessInput {
  public:
    //constructors
    WirelessInput(uint8_t s = 0);

    //designate the serial port to be used.
    //Supports Serial, Serial1, Serial2, and Serial3
    void setSerial(uint8_t s);

    //start the serial port communication and
    //reduce the timeout so parseInt doesn't wait 60 seconds
    void begin(int baud = BAUD);

    //get any new data waiting on the serial monitor
    void refresh();

    //get the stored information about the joysticks
    int getJoystick(char joy);
    int getJoystick(char leftright, char xy);
    //get the stored information about button states
    boolean pressed(char button);
    boolean isPressed(char button);


  private:
    //private variables to store controller states
    int x[2];
    int y[2];
    boolean button1, button2, button3, button4,
            buttonL1, buttonL2, buttonR1, buttonR2,
            buttonU, buttonD, buttonL, buttonR,
            buttonLJ, buttonRJ, buttonStart, buttonSelect;

    //pointer to serial port being used. Default Serial
    HardwareSerial* serial;

    //zero out all controller states in case not all are present
    void setInitialValues();
    void printInputs();
};

#endif
