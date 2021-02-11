/*****************************************************
 *
 * Rivers Robotics Library
 * Yoshiro Fujita, 2019
 * For use in The Rivers School Robotics program
 *
 * Includes all classes necessary for use in the Rivers
 * Robotics program.
 *
 * In development is an alternate format that further
 * simplifies the programming process, automatically
 * declaring setup() and loop() to automatically
 * establish and refresh connections with wireless
 * gamepad controllers. If this is used, students would
 * NOT define their own setup() and loop(), but would
 * instead use robotLoop() and place their code there.
 *
 * Further instantiates predefined motor objects
 * based on different drive types like differential
 * and omni drive.
 *
 *****************************************************/
#include "RiversWirelessInput.h"
#include "RiversMotor.h"
#include "RiversServomotor.h"
#include "RiversLCD.h"
#include "RiversTime.h"
#include "RiversIO.h"
#include "RiversEngineering.h"
#include "RiversTFLuna.h"


// handles predefining things for simple student code
#ifdef SIMPLE


// where student code goes
extern void robotLoop();


// Different Defines for motors based on drive type
#if defined DIFFERENTIAL
Motor leftMotor(MCA1), rightMotor(MCA2), motorB1(MCB1), motorB2(MCB2);
#elif defined OMNI_PLUS
Motor leftMotor(MCA1), rightMotor(MCA2), frontMotor(MCB1), backMotor(MCB2);
#elif defined OMNI_X
Motor frontLeftMotor(MCA1), frontRightMotor(MCA2), backLeftMotor(MCB1), backRightMotor(MCB2);
#else
Motor motorA1(MCA1), motorA2(MCA2), motorB1(MCB1), motorB2(MCB2);
#endif

Servomotor servoA(SERVO_A), servoB(SERVO_B), servoC(SERVO_C), servoD(SERVO_D);

WirelessInput gamepad;

LCD lcd;

struct Joystick {
  int x, y;
};

class Button {
  private:
    boolean val = false;
  public:
    Button() {}
    boolean isPressed() {
      return val;
    }
    void operator = (boolean b) {
      val = b;
    };
};

Joystick leftJoy, rightJoy;
Button button1, button2, button3, button4, leftTrigger1, leftTrigger2, rightTrigger1, rightTrigger2, up, down, left, right, start, select, leftJoyButton, rightJoyButton;

void setup() {
  gamepad.begin(9600);
  lcd.startup();
}

void loop() {
  gamepad.refresh();
  leftJoy.x = gamepad.getJoystick(LEFT_X);
  leftJoy.y = gamepad.getJoystick(LEFT_Y);
  rightJoy.x = gamepad.getJoystick(RIGHT_X);
  rightJoy.y = gamepad.getJoystick(RIGHT_Y);
  button1 = gamepad.pressed(BUTTON_1);
  button2 = gamepad.pressed(BUTTON_2);
  button3 = gamepad.pressed(BUTTON_3);
  button4 = gamepad.pressed(BUTTON_4);
  leftTrigger1 = gamepad.pressed(BUTTON_L1);
  leftTrigger2 = gamepad.pressed(BUTTON_L2);
  rightTrigger1 = gamepad.pressed(BUTTON_R1);
  rightTrigger2 = gamepad.pressed(BUTTON_R2);
  up = gamepad.pressed(BUTTON_UP);
  down = gamepad.pressed(BUTTON_DOWN);
  left = gamepad.pressed(BUTTON_LEFT);
  right = gamepad.pressed(BUTTON_RIGHT);
  start = gamepad.pressed(BUTTON_START);
  select = gamepad.pressed(BUTTON_SELECT);
  leftJoyButton = gamepad.pressed(BUTTON_LJOY);
  rightJoyButton = gamepad.pressed(BUTTON_RJOY);

  robotLoop();
}

boolean isPressed(char button) {
  return gamepad.pressed(button);
}

#endif
