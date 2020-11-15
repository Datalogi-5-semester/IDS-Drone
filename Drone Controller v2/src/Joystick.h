#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"
#include "Button.h"

class Joystick {
public:

  int xPin = 0;
  int yPin = 0;
  
  Joystick(int xPin, int yPin) {
    this->xPin = xPin;
    this->yPin = yPin;
  };

  int getJoystickValuesX() {
    int xVal = analogRead(this->xPin);
    return xVal;
  }

  int getJoystickValuesY() {
    int yVal = analogRead(this->yPin);
    return yVal;
  }

};

#endif