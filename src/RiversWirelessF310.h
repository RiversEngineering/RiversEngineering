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

#define SerialTransmit Serial1

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
    JoystickEvents();
    void OnGamePadChanged(const GamePadEventData *evt);
};




class JoystickReportParser : public HIDReportParser {
    JoystickEvents *joyEvents;

    uint8_t oldPad[RPT_GEMEPAD_LEN];
    uint8_t oldHat;
    uint16_t oldButtons;

  public:
    JoystickReportParser(JoystickEvents *evt);
    void Parse(HID *hid, uint32_t is_rpt_id, uint32_t len, uint8_t *buf);
};








/*******************************************************************************
                                                        WirelessGamepad class

  For use with the DFRobot Wireless Gamepad. Implements the wireless protocol
  used here on the sending side, allowing for easy teleop of robot.

  Sends a new packet every 60 ms (about as fast as could work reliably in tests)
 *******************************************************************************/
class WirelessF310 {
  public:
    WirelessF310();
    void begin(int baud = BAUD);
    void transmit();
    void setDelay(int d);

  private:
    int _delay = 60;
    USBHost UsbH;
    USBHub* Hub;
    HIDUniversal* Hid;
    JoystickEvents JoyEvents;
    JoystickReportParser* Joy;
};

#endif
