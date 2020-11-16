/*****************************************************
 * 
 * Rivers General IO Library
 * Yoshiro Fujita, 2019
 * For use in The Rivers School Engineering program
 * 
 * Implements several classes for basic circuit elements.
 * Classes include:
 * Buttons
 * Piezoelectric Buzzers
 * LEDs
 * Generic Digital Input
 * Generic Analog Input
 * Potentiometers
 * Analog Pulse Sensor
 * Analog Light Sensor
 * 
 * Also implements a NeoPixel wrapper class that makes
 * code more intuitive for students, if somewhat more
 * wordy. Two NeoPixel classes are currently included 
 * (NeoPixel and Neopixel). The former is for legacy 
 * support and is considered deprecated. It may be 
 * removed in the future.
 * 
 * This library, and other associated libraries, are 
 * written with the goal of making Arduino code more 
 * readable for beginning students. It is NOT written
 * with experienced users in mind, and is thus fairly 
 * limited in usability for more complex applications.
 * The goal is simplicity and ease of understanding, 
 * not flexibility and complexity.
 * 
 * Requires that the Adafruit NeoPixel library be installed.
 * 
 *****************************************************/
#ifndef IO_H
#define IO_H

#include <Adafruit_NeoPixel.h>


class Input {
  public:
    Input() {}
    int read();
};

class Output {
  public:
    Output() {}
    void set(int);
};


/*******************************************************************************
                                                        Button class

  For use with buttons that when pressed connect an input pin to ground.
  Can detect transitions from not pressed to pressed (HIGH -> LOW)
  or from pressed to not pressed (LOW -> HIGH)
 *******************************************************************************/
class Button : public Input {
  private:
    uint8_t pin;
    boolean wasPressedLast = false;
    boolean pressedState = HIGH;
  public:
    Button();
    void attach(int p);
    void isAttachedTo(int p);
    int read();
    void setPressedState(boolean ps);
    boolean isPressed();
    boolean transitionPressed();
    boolean transitionReleased();
};



/*******************************************************************************
                                                        LED class

  For use with simple LEDs connected to an input pin.
  Can be configured so that HIGH turns the LED on (default), or LOW.
  Also can use PWM pins for varying brightness.
  Don't forget to use a current limiting resistor so LEDs aren't blown out.
 *******************************************************************************/
class Buzzer : public Output {
  private:
    int pin;
  public:
    Buzzer();
    void attach(int p);
    void isAttachedTo(int p);
    void play(int frequency);
    void play();
    void stop();
};


/*******************************************************************************
                                                        LED class

  For use with simple LEDs connected to an input pin.
  Can be configured so that HIGH turns the LED on (default), or LOW.
  Also can use PWM pins for varying brightness.
  Don't forget to use a current limiting resistor so LEDs aren't blown out.
 *******************************************************************************/
class SimpleLED : public Output {
  private:
    uint8_t pin;
    boolean onState = HIGH;
  public:
    SimpleLED();
    void attach(int p);
    void isAttachedTo(int p);
    void setActiveLow();
    void setActiveHigh();
    void setActive(boolean b);
    void on();
    void turnOn();
    void set(int on);
    void off();
    void turnOff();
    void set(boolean state);
    void setBrightness(int pwm);
};



/*******************************************************************************
                                                        DigitalInput class

  A generic digital input.
  Implements boolean == comparison operator override.
 *******************************************************************************/
class DigitalInput : Input {
  private:
    uint8_t pin;
  public:
    DigitalInput();
    void attach(int p);
    void isAttachedTo(int p);
    void attach(int p, int mode);
    void isAttachedTo(int p, int mode);
    int read();
    boolean operator == (boolean b);
};



/*******************************************************************************
                                                        AnalogInput class

  A generic analog input class.
  Overrides boolean comparison operators
 *******************************************************************************/
class AnalogInput : Input {
  private:
    uint8_t pin;
  public:
    AnalogInput();
    void attach(int p);
    void isAttachedTo(int p);
    int read();

    boolean operator == (int x);
    boolean operator >= (int x);
    boolean operator <= (int x);
    boolean operator > (int x);
    boolean operator < (int x);
    boolean operator != (int x);
};




/*******************************************************************************
                                                        Potentiometer class
 *******************************************************************************/
class Potentiometer : public AnalogInput {
    //just the same as AnalogInput
};



/*******************************************************************************
                                                  Analog Light Sensor class
 *******************************************************************************/
class LightSensor : public AnalogInput {
    //just the same as AnalogInput
};



/*******************************************************************************
                                                  Pulse Sensor class
 *******************************************************************************/
class Pulse : public AnalogInput {

};




class LED : public Output {
  private:
    Adafruit_NeoPixel pix;
    int numPix = 1;
    int pin = 3;
    int R = 100;
    int G = 0;
    int B = 0;

  public:
    LED();
    void attach(int p);
    void isAttachedTo(int p);
    void set(int r, int g, int b);
    void setColor(int r, int g, int b);
};



#endif
