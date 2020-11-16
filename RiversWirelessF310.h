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

#include "RiversWirelessProtocol.h"
#include <hid.h>
#include <hiduniversal.h>
#include <usbhub.h>

#define SerialDebug Serial1

#define RPT_GEMEPAD_LEN    6

#define BAUD 115200


#define YMASK 128
#define BMASK 64
#define AMASK 32
#define XMASK 16
#define RJMASK 128
#define LJMASK 64
#define STMASK 32
#define BKMASK 16
#define R2MASK 8
#define L2MASK 4
#define R1MASK 2
#define L1MASK 1
#define MDMASK 8
#define DPAD_MASK 15




struct GamePadEventData {
  uint8_t LX, LY, RX, RY, BT1, BT2, MD;
};


class JoystickEvents {
  public:
    void OnGamePadChanged(const GamePadEventData *evt) {
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

      SerialDebug.print(packet);
      SerialDebug.println();
    }
};




class JoystickReportParser : public HIDReportParser {
    JoystickEvents *joyEvents;

    uint8_t oldPad[RPT_GEMEPAD_LEN];
    uint8_t oldHat;
    uint16_t oldButtons;

  public:
    JoystickReportParser(JoystickEvents *evt) :
      joyEvents(evt),
      oldHat(0xDE),
      oldButtons(0) {
      for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
        oldPad[i] = 0xD;
    }
    void Parse(HID *hid, uint32_t is_rpt_id, uint32_t len, uint8_t *buf) {
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
};






USBHost UsbH;
USBHub Hub(&UsbH);
HIDUniversal Hid(&UsbH);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);






/*******************************************************************************
                                                        WirelessGamepad class

  For use with the DFRobot Wireless Gamepad. Implements the wireless protocol
  used here on the sending side, allowing for easy teleop of robot. 

  Sends a new packet every 60 ms (about as fast as could work reliably in tests)
 *******************************************************************************/
class WirelessGamepad {
  public:
    WirelessGamepad() {
    }


    void begin(int baud = BAUD) {
      SerialDebug.begin(baud);
      //SerialDebug.println("Start");

      if (UsbH.Init())
        //SerialDebug.println("USB host did not start.");

      delay(200);

      if (!Hid.SetReportParser(0, &Joy))
        ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
    };


    void transmit() {

      UsbH.Task();
    };

    void setDelay(int d) {
      _delay = d;
    };
  private:
    int _delay = 60;
    int _xLOffset = 0;
    int _xROffset = 0;
    int _yLOffset = 0;
    int _yROffset = 0;
};

#endif
