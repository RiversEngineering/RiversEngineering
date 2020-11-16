#include "RiversWirelessInput.h"


WirelessInput::WirelessInput(uint8_t s) {
  setSerial(s);
  setInitialValues();
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





void WirelessInput::begin(int baud) {
  serial->begin(baud);
  serial->setTimeout(5);
};









void WirelessInput::refresh() {
  while (serial->available())
  {
    char key = serial->read();

    switch (key) {
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





int WirelessInput::getJoystick(char joy) {
  switch (joy) {
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






int WirelessInput::getJoystick(char leftright, char xy) {
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





boolean WirelessInput::pressed(char button) {
  switch (button) {
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






boolean WirelessInput::isPressed(char button) {
  return pressed(button);
}







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
