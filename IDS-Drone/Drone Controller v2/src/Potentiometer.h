#include <Arduino.h>

class Potentiometer {
  public:

  int potentiometerPin = 0;

  Potentiometer(int potentiometerPin){
    this->potentiometerPin = potentiometerPin;
  }

  int getPotentiometerValue(){
    int potentiometerValue = analogRead(this->potentiometerPin);
    return potentiometerValue;
  }
};