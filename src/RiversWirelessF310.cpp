#include "RiversWirelessF310.h"

JoystickEvents::JoystickEvents() {
}
void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt) {
  String packet = "";

  packet += LEFT_X;
  packet += map(evt->LX, 0, 255, -255, 255);
  packet += LEFT_Y;
  packet += map(evt->LY, 0, 255, 255, -255);
  packet += RIGHT_X;
  packet += map(evt->RX, 0, 255, -255, 255);
  packet += RIGHT_Y;
  packet += map(evt->RY, 0, 255, 255, -255);

  packet += BUTTON_A;
  if (evt->BT1 & AMASK)
    packet += '1';
  else packet += '0';
  packet += BUTTON_B;
  if (evt->BT1 & BMASK)
    packet += '1';
  else packet += '0';
  packet += BUTTON_X;
  if (evt->BT1 & XMASK)
    packet += '1';
  else packet += '0';
  packet += BUTTON_Y;
  if (evt->BT1 & YMASK)
    packet += '1';
  else packet += '0';

  int dpad = (int)(evt->BT1 & DPAD_MASK);
  packet += BUTTON_UP;
  if (dpad < 2 || dpad == 7)
    packet += '1';
  else packet += '0';
  packet += BUTTON_DOWN;
  if (dpad < 6 && dpad > 2)
    packet += '1';
  else packet += '0';
  packet += BUTTON_LEFT;
  if (dpad < 8 && dpad > 4)
    packet += '1';
  else packet += '0';
  packet += BUTTON_RIGHT;
  if (dpad < 4 && dpad > 0)
    packet += '1';
  else packet += '0';

  packet += BUTTON_L1;
  if (evt->BT2 & L1MASK)
    packet += '1';
  else packet += '0';
  packet += BUTTON_L2;
  if (evt->BT2 & L2MASK)
    packet += '1';
  else packet += '0';
  packet += BUTTON_R1;
  if (evt->BT2 & R1MASK)
    packet += '1';
  else packet += '0';
  packet += BUTTON_R2;
  if (evt->BT2 & R2MASK)
    packet += '1';
  else packet += '0';

  packet += BUTTON_LJOY;
  if (evt->BT2 & LJMASK)
    packet += '1';
  else packet += '0';
  packet += BUTTON_RJOY;
  if (evt->BT2 & RJMASK)
    packet += '1';
  else packet += '0';
  packet += BUTTON_START;
  if (evt->BT2 & STMASK)
    packet += '1';
  else packet += '0';
  packet += BUTTON_SELECT;
  if (evt->BT2 & BKMASK)
    packet += '1';
  else packet += '0';

  SerialTransmit.print(packet);
}





JoystickReportParser::JoystickReportParser(JoystickEvents *evt) : joyEvents(evt), oldHat(0xDE),   oldButtons(0) {
  for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
    oldPad[i] = 0xD;
}
void JoystickReportParser::Parse(HID *hid, uint32_t is_rpt_id, uint32_t len, uint8_t *buf) {
  bool match = true;

  // Checking if there are changes in report since the method was last called
  for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
    if (buf[i] != oldPad[i]) {
      match = false;
      break;
    }

  // Calling Game Pad event handler
  if (!match && joyEvents) {
    joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

    for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
      oldPad[i] = buf[i];
  }
}






WirelessF310::WirelessF310() {
}


void WirelessF310::begin(int baud) {
  SerialTransmit.begin(baud);
  //SerialDebug.println("Start");

  if (UsbH.Init())
    //SerialDebug.println("USB host did not start.");

  delay(200);

  if (!Hid.SetReportParser(0, &Joy))
    ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
};


void WirelessF310::transmit() {

  UsbH.Task();
};

void WirelessF310::setDelay(int d) {
  _delay = d;
};
