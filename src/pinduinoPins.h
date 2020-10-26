/*
  pinduino.h - Library for pinduino shield for Arduinos.
  Created by Eric Lyons and Wes Sparks, 2015.
  Released into the public domain.
  Play more pinball!
*/
#ifndef pinduinoPins_h
#define pinduinoPins_h

#include <Arduino.h>

class pinduinoPins {
protected:

public:
    //Constructor
    pinduinoPins();

    pinduinoPins(String val);

    //Variables
    String controllerType;

    //Arduino pin functions
    void reset(); // resets values of all pin states to 0
    void resetPin(int pin); // resets the value of a pin State to 0
    void print(); // print values of pin states
    void update(); // update pin states by scanning input pins
    bool get(int pin); // gets the pin state for a given Arduino pin
    bool any(); // returns true if any pinStates have non-zero values
    int numPins(); // returns the number of pins being monitors (default: 16)

    bool J6(int pin); // interface to retrieve pin state by Stern J6 pin
    void resetJ6(int pin); // interface to retrieve pin state by Stern J6 pin
    bool J7(int pin); // interface to retrieve pin state by Stern J7 pin
    void resetJ7(int pin); // interface to retrieve pin state by Stern J7 pin

    // WPC
    bool J3(int pin);
    void resetJ3(int pin);
    bool J122(int pin);
    void resetJ122(int pin);
    bool J123(int pin);
    void resetJ123(int pin);
    bool J124(int pin);
    void resetJ124(int pin);
    bool J125(int pin);
    void resetJ125(int pin);
    bool J126(int pin);
    void resetJ126(int pin);

    // WPC95
    bool J110(int pin); // interface to retrieve pin state by WPC95 J110 pin
    void resetJ110(int pin); // interface to retrieve pin state by WPC95 J110 pin
    bool J111(int pin); // interface to retrieve pin state by WPC95 J111 pin
    void resetJ111(int pin); // interface to retrieve pin state by WPC95 J111 pin

    bool J9(int pin); // interface to retrieve pin state by Data East/Sega System 3 pin
    void resetJ9(int pin); // interface to retrieve pin state by Data East/Sega System 3
    bool P11(int pin); // interface to retrieve pin state for System 11
    void resetP11(int pin); // interface to retrieve pin state for System 11
    bool P12(int pin); // interface to retrieve pin state for System 11
    void resetP12(int pin); // interface to retrieve pin state for System 11

private:
    //internal array for input pins getting signal from pinball machine
    const static int _numPins = 30;
    int _pins[_numPins];
    bool _pinStates[_numPins];
};


#endif
