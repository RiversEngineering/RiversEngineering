#include "RiversWirelessGamepadShield.h"


WirelessGamepadShield::WirelessGamepadShield() {
};
void WirelessGamepadShield::begin(int baud) {
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
void WirelessGamepadShield::transmit() {
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

void WirelessGamepadShield::setDelay(int d) {
  _delay = d;
};
