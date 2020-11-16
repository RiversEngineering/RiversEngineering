#include "RiversWirelessGamepad.h"

WirelessGamepad::WirelessGamepad() {
};



void WirelessGamepad::begin(int baud) {
  Serial.begin(baud);
  Serial1.begin(baud);

  pinMode(LEFTX_PIN, INPUT);
  pinMode(LEFTY_PIN, INPUT);
  pinMode(RIGHTX_PIN, INPUT);
  pinMode(RIGHTY_PIN, INPUT);

  //Joystick buttons
  pinMode(B_LEFTSTICK_PIN, INPUT);
  pinMode(B_RIGHTSTICK_PIN, INPUT);

  //Buttons
  pinMode(B1_PIN, INPUT);
  pinMode(B2_PIN, INPUT);
  pinMode(B3_PIN, INPUT);
  pinMode(B4_PIN, INPUT);

  //Shoulder Buttons
  pinMode(L1_PIN, INPUT);
  pinMode(L2_PIN, INPUT);
  pinMode(R1_PIN, INPUT);
  pinMode(R2_PIN, INPUT);

  //Dpad
  pinMode(UP_PIN, INPUT);
  pinMode(DOWN_PIN, INPUT);
  pinMode(LEFT_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);

  //Other
  pinMode(START_PIN, INPUT);
  pinMode(SELECT_PIN, INPUT);

  //Outputs
  pinMode(VIBRATION_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

#ifdef CALIBRATE_ON_STARTUP
  for (int i = 0; i < 10; i++)
  {
    _xLOffset += analogRead(LEFTX_PIN);
    _xROffset += analogRead(RIGHTX_PIN);
    _yLOffset += analogRead(LEFTY_PIN);
    _yROffset += analogRead(RIGHTY_PIN);
  }

  _xLOffset /= 10;
  _xROffset /= 10;
  _yLOffset /= 10;
  _yROffset /= 10;

  _xLOffset = 512 - _xLOffset;
  _xROffset = 512 - _xROffset;
  _yLOffset = 512 - _yLOffset;
  _yROffset = 512 - _yROffset;
#endif
};





void WirelessGamepad::transmit() {
#ifdef UPDATE_ONLY
  // transmit only when changes are detected
  current = LEFT_X;
  current += (int)map(analogRead(LEFTX_PIN) + _xLOffset, 0, 1023, 255, -255);
  current += LEFT_Y;
  current += (int)map(analogRead(LEFTY_PIN) + _yLOffset, 0, 1023, -255, 255);
  current += RIGHT_X;
  current += (int)map(analogRead(RIGHTX_PIN) + _xROffset, 0, 1023, 255, -255);
  current += RIGHT_Y;
  current += (int)map(analogRead(RIGHTY_PIN) + _yROffset, 0, 1023, -255, 255);

  current += BUTTON_1;
  if (!digitalRead(B1_PIN))
    current += '1';
  else current += '0';
  current += BUTTON_2;
  if (!digitalRead(B2_PIN))
    current += '1';
  else current += '0';
  current += BUTTON_3;
  if (!digitalRead(B3_PIN))
    current += '1';
  else current += '0';
  current += BUTTON_4;
  if (!digitalRead(B4_PIN))
    current += '1';
  else current += '0';

  current += BUTTON_UP;
  if (!digitalRead(UP_PIN))
    current += '1';
  else current += '0';
  current += BUTTON_DOWN;
  if (!digitalRead(DOWN_PIN))
    current += '1';
  else current += '0';
  current += BUTTON_LEFT;
  if (!digitalRead(LEFT_PIN))
    current += '1';
  else current += '0';
  current += BUTTON_RIGHT;
  if (!digitalRead(RIGHT_PIN))
    current += '1';
  else current += '0';

  current += BUTTON_L1;
  if (!digitalRead(L1_PIN))
    current += '1';
  else current += '0';
  current += BUTTON_L2;
  if (!digitalRead(L2_PIN))
    current += '1';
  else current += '0';
  current += BUTTON_R1;
  if (!digitalRead(R1_PIN))
    current += '1';
  else current += '0';
  current += BUTTON_R2;
  if (!digitalRead(R2_PIN))
    current += '1';
  else current += '0';

  current += BUTTON_LJOY;
  if (!digitalRead(B_LEFTSTICK_PIN))
    current += '1';
  else current += '0';
  current += BUTTON_RJOY;
  if (!digitalRead(B_RIGHTSTICK_PIN))
    current += '1';
  else current += '0';
  current += BUTTON_START;
  if (!digitalRead(START_PIN))
    current += '1';
  else current += '0';
  current += BUTTON_SELECT;
  if (!digitalRead(SELECT_PIN))
    current += '1';
  else current += '0';

  if (current != previous) {
    current.print((HardwareSerial*)&Serial1);
    current.println((HardwareSerial*)&Serial);
  }
  previous = current;
#else
  // produce a constant stream based on delay rather than only on a change in values
  long now;
  long start = millis();
  int remainingDelay = 0;
  String packet = "";

  packet += LEFT_X;
  packet += map(analogRead(LEFTX_PIN) + _xLOffset, 0, 1023, 255, -255);
  packet += LEFT_Y;
  packet += map(analogRead(LEFTY_PIN) + _yLOffset, 0, 1023, -255, 255);
  packet += RIGHT_X;
  packet += map(analogRead(RIGHTX_PIN) + _xROffset, 0, 1023, 255, -255);
  packet += RIGHT_Y;
  packet += map(analogRead(RIGHTY_PIN) + _yROffset, 0, 1023, -255, 255);

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

  packet += BUTTON_UP;
  if (!digitalRead(UP_PIN))
    packet += '1';
  else packet += '0';
  packet += BUTTON_DOWN;
  if (!digitalRead(DOWN_PIN))
    packet += '1';
  else packet += '0';
  packet += BUTTON_LEFT;
  if (!digitalRead(LEFT_PIN))
    packet += '1';
  else packet += '0';
  packet += BUTTON_RIGHT;
  if (!digitalRead(RIGHT_PIN))
    packet += '1';
  else packet += '0';

  packet += BUTTON_L1;
  if (!digitalRead(L1_PIN))
    packet += '1';
  else packet += '0';
  packet += BUTTON_L2;
  if (!digitalRead(L2_PIN))
    packet += '1';
  else packet += '0';
  packet += BUTTON_R1;
  if (!digitalRead(R1_PIN))
    packet += '1';
  else packet += '0';
  packet += BUTTON_R2;
  if (!digitalRead(R2_PIN))
    packet += '1';
  else packet += '0';

  packet += BUTTON_LJOY;
  if (!digitalRead(B_LEFTSTICK_PIN))
    packet += '1';
  else packet += '0';
  packet += BUTTON_RJOY;
  if (!digitalRead(B_RIGHTSTICK_PIN))
    packet += '1';
  else packet += '0';
  packet += BUTTON_START;
  if (!digitalRead(START_PIN))
    packet += '1';
  else packet += '0';
  packet += BUTTON_SELECT;
  if (!digitalRead(SELECT_PIN))
    packet += '1';
  else packet += '0';

  Serial1.print(packet);
  Serial.println(packet);
#endif

  // Check to see if vibrate or LED commands received
  while (Serial1.available())
  {
    char key = Serial1.read();

    switch (key) {
      case 'v':
        if (Serial1.read() == '1')
          digitalWrite(VIBRATION_PIN, HIGH);
        else digitalWrite(VIBRATION_PIN, LOW);
        break;
      case 'o':
        if (Serial1.read() == '1')
          digitalWrite(LED_PIN, HIGH);
        else digitalWrite(LED_PIN, LOW);
        break;
    }
  }

#ifndef UPDATE_ONLY
  // Delay the appropriate remaining time if producing a constant stream instead of updates alone.
  now = millis();
  remainingDelay = _delay - (now - start);
  if (remainingDelay > 0)
    delay(remainingDelay);
#endif
};

void WirelessGamepad::setDelay(int d) {
  _delay = d;
};
