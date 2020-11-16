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
#ifndef WIRELESS_CONTROLLER_H
#define WIRELESS_CONTROLLER_H
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
    WirelessInput() {
      setSerial(0);
      setInitialValues();
    };
    WirelessInput(uint8_t s) {
      setSerial(s);
      setInitialValues();
    };

    //designate the serial port to be used.
    //Supports Serial, Serial1, Serial2, and Serial3
    void setSerial(uint8_t s);
    void attach(uint8_t s);

    //start the serial port communication and
    //reduce the timeout so parseInt doesn't wait 60 seconds
    void begin(int baud);

    //get any new data waiting on the serial monitor
    void refresh();

    //get the stored information about the joysticks
    int getJoystick(char joy);
    int getJoystick(char leftright, char xy) {
      if (leftright == LEFT) {
        if (xy == X)
          return this->getJoystick(LEFT_X);
        else if (xy == Y)
          return this->getJoystick(LEFT_Y);
      }
      else if (leftright == RIGHT) {
        if (xy == X)
          return this->getJoystick(RIGHT_X);
        else if (xy == Y)
          return this->getJoystick(RIGHT_Y);
      }
      return 0;
    }
    int leftJoystickHorizontal() {
      return getJoystick(LEFT_X);
    }
    int leftJoystickVertical() {
      return getJoystick(LEFT_Y);
    }
    int rightJoystickHorizontal() {
      return getJoystick(RIGHT_X);
    }
    int rightJoystickVertical() {
      return getJoystick(RIGHT_Y);
    }

    //get the stored information about button states
    boolean pressed(char button);
    boolean isPressed(char button) {
      return pressed(button);
    }


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

class XBee : public WirelessInput {

};



void WirelessInput::setSerial(uint8_t s) {
  switch (s) {
    default:
    case 0:
      serial = (HardwareSerial*)(&Serial);
      break;

#ifdef SERIAL1 //only include this if Serial1 exists
    case 1:
      serial = &Serial1;
      break;
#endif

#ifdef SERIAL23 //only include this if Serial2/3 exist
    case 2:
      serial = &Serial2;
      break;
    case 3:
      serial = &Serial3;
      break;
#endif

  }
};
void WirelessInput::attach(uint8_t s) {
  this->setSerial(s);
};
void WirelessInput::refresh() {
  while (serial->available())
  {
    char key = serial->read();

    switch (key)
    {
      case LEFT_X:
        x[0] = serial->parseInt();
        break;
      case LEFT_Y:
        y[0] = serial->parseInt();
        break;
      case RIGHT_X:
        x[1] = serial->parseInt();
        break;
      case RIGHT_Y:
        y[1] = serial->parseInt();
        break;

      case BUTTON_1:
        button1 = serial->parseInt();
        break;
      case BUTTON_2:
        button2 = serial->parseInt();
        break;
      case BUTTON_3:
        button3 = serial->parseInt();
        break;
      case BUTTON_4:
        button4 = serial->parseInt();
        break;

      case BUTTON_UP:
        buttonU = serial->parseInt();
        break;
      case BUTTON_DOWN:
        buttonD = serial->parseInt();
        break;
      case BUTTON_LEFT:
        buttonL = serial->parseInt();
        break;
      case BUTTON_RIGHT:
        buttonR = serial->parseInt();
        break;

      case BUTTON_L1:
        buttonL1 = serial->parseInt();
        break;
      case BUTTON_L2:
        buttonL2 = serial->parseInt();
        break;
      case BUTTON_R1:
        buttonR1 = serial->parseInt();
        break;
      case BUTTON_R2:
        buttonR2 = serial->parseInt();
        break;

      case BUTTON_LJOY:
        buttonLJ = serial->parseInt();
        break;
      case BUTTON_RJOY:
        buttonRJ = serial->parseInt();
        break;
      case BUTTON_START:
        buttonStart = serial->parseInt();
        break;
      case BUTTON_SELECT:
        buttonSelect = serial->parseInt();
        break;
    }
  }
};
void WirelessInput::begin(int baud = BAUD) {
  serial->begin(baud);
  serial->setTimeout(5);
};
int WirelessInput::getJoystick(char joy) {
  switch (joy)
  {
    case LEFT_X:
      return x[0];
      break;
    case LEFT_Y:
      return y[0];
      break;
    case RIGHT_X:
      return x[1];
      break;
    case RIGHT_Y:
      return y[1];
      break;
    default:
      return 0;
      break;
  }
};
boolean WirelessInput::pressed(char button) {
  switch (button)
  {
    case BUTTON_1:
      return (button1 != 0);
    case BUTTON_2:
      return (button2 != 0);
    case BUTTON_3:
      return (button3 != 0);
    case BUTTON_4:
      return (button4 != 0);

    case BUTTON_UP:
      return (buttonU != 0);
    case BUTTON_DOWN:
      return (buttonD != 0);
    case BUTTON_LEFT:
      return (buttonL != 0);
    case BUTTON_RIGHT:
      return (buttonR != 0);

    case BUTTON_L1:
      return (buttonL1 != 0);
    case BUTTON_L2:
      return (buttonL2 != 0);
    case BUTTON_R1:
      return (buttonR1 != 0);
    case BUTTON_R2:
      return (buttonR2 != 0);

    case BUTTON_START:
      return (buttonStart != 0);
    case BUTTON_SELECT:
      return (buttonSelect != 0);
    case BUTTON_LJOY:
      return (buttonLJ != 0);
    case BUTTON_RJOY:
      return (buttonRJ != 0);


    default:
      return false;
  }
};
void WirelessInput::setInitialValues() {
  button1 = false;
  button2 = false;
  button3 = false;
  button4 = false;

  buttonL1 = false;
  buttonL2 = false;
  buttonR1 = false;
  buttonR2 = false;

  buttonU = false;
  buttonD = false;
  buttonL = false;
  buttonR = false;

  buttonLJ = false;
  buttonRJ = false;
  buttonStart = false;
  buttonSelect = false;

  x[0] = 0;
  y[0] = 0;
  x[1] = 0;
  y[1] = 0;
};
void WirelessInput::printInputs() {
  Serial.print(this->getJoystick(LEFT_X));
  Serial.print("\t");
  Serial.print(this->getJoystick(LEFT_Y));
  Serial.print("\t");
  Serial.print(this->getJoystick(RIGHT_X));
  Serial.print("\t");
  Serial.print(this->getJoystick(RIGHT_Y));
  Serial.print("\t");
  if (this->pressed(BUTTON_1))
    Serial.print("1\t");
  if (this->pressed(BUTTON_2))
    Serial.print("2\t");
  if (this->pressed(BUTTON_3))
    Serial.print("3\t");
  if (this->pressed(BUTTON_4))
    Serial.print("4\t");
  if (this->pressed(BUTTON_UP))
    Serial.print("UP\t");
  if (this->pressed(BUTTON_DOWN))
    Serial.print("DOWN\t");
  if (this->pressed(BUTTON_LEFT))
    Serial.print("LEFT\t");
  if (this->pressed(BUTTON_RIGHT))
    Serial.print("RIGHT\t");
  if (this->pressed(BUTTON_L1))
    Serial.print("L1\t");
  if (this->pressed(BUTTON_L2))
    Serial.print("L2\t");
  if (this->pressed(BUTTON_R1))
    Serial.print("R1\t");
  if (this->pressed(BUTTON_R2))
    Serial.print("R2\t");
  if (this->pressed(BUTTON_LJOY))
    Serial.print("LJOY\t");
  if (this->pressed(BUTTON_RJOY))
    Serial.print("RJOY\t");
  if (this->pressed(BUTTON_START))
    Serial.print("START\t");
  if (this->pressed(BUTTON_SELECT))
    Serial.print("SELECT\t");
  Serial.println();
};
#endif
#endif
