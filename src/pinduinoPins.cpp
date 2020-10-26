#include "pinduinoPins.h"

pinduinoPins::pinduinoPins(String val) {
	controllerType = val;

    if (controllerType == "PPUC-Arduino-1.0.0") {
        _pins[0] = 8;
        _pins[1] = 9;
        _pins[2] = 10;
        _pins[3] = 11;
        _pins[4] = 12;
        _pins[5] = 13;
        _pins[6] = 30;
        _pins[7] = 31;
        _pins[8] = 32;
        _pins[9] = 33;
        _pins[10] = 34;
        _pins[11] = 35;
        _pins[12] = 36;
        _pins[13] = 37;
        _pins[14] = 38;
        _pins[15] = 39;
        _pins[16] = 40;
        _pins[17] = 41;
        _pins[18] = 42;
        _pins[19] = 43;
        _pins[20] = 44;
        _pins[21] = 45;
        _pins[22] = 46;
        _pins[23] = 47;
        _pins[24] = 48;
        _pins[25] = 49;
        _pins[26] = 50;
        _pins[27] = 51;
        _pins[28] = 52;
        _pins[29] = 53;
    }
    else if (controllerType == "PPUC-Teensy-1.0.0") {
        _pins[0] = -1;
        _pins[1] = -1;
        _pins[2] = -1;
        _pins[4] = -1;
        _pins[3] = -1;
        _pins[5] = -1;
        _pins[6] = -1;
        _pins[7] = -1;
        _pins[8] = -1;
        _pins[9] = -1;
        _pins[10] = -1;
        _pins[11] = -1;
        _pins[12] = -1;
        _pins[13] = -1;
        _pins[14] = -1;
        _pins[15] = -1;
        _pins[16] = -1;
        _pins[17] = -1;
        _pins[18] = -1;
        _pins[19] = -1;
        _pins[20] = -1;
        _pins[21] = -1;
        _pins[22] = -1;
        _pins[23] = -1;
        _pins[24] = -1;
        _pins[25] = -1;
        _pins[24] = -1;
        _pins[27] = -1;
        _pins[28] = -1;
        _pins[29] = -1;
    }

    for (int i = 0; i < _numPins; i++) {
        pinMode(_pins[i], INPUT);
        _pinStates[i] = false;
    }
}

void pinduinoPins::reset() {
	for (int i = 0; i < _numPins; i++) {
		_pinStates[i] = 0;    
	}
}

void pinduinoPins::resetPin(int pin) {
	_pinStates[pin] = 0;
}

bool pinduinoPins::get(int pin) {
	return _pinStates[pin];
}

bool pinduinoPins::any() {
	for (int i = 0; i < _numPins; i++) {
		if (_pinStates[i]) {
		    return true;
		}
	}
	return false;
}

bool pinduinoPins::J7 (int pin) {
    return false;
}

void pinduinoPins::resetJ7 (int pin) {
}

bool pinduinoPins::J6 (int pin) {
    return false;
}

void pinduinoPins::resetJ6 (int pin) {
}

bool pinduinoPins::J122(int pin) {
	if      (pin == 1) { return get(6); }
	else if (pin == 2) { return get(7); }
	else if (pin == 3) { return get(8); }
    else if (pin == 4) { return get(9); }
	else if (pin == 5) { return get(10); }
	else if (pin == 6) { return get(11); }
    // 7 is key
	else if (pin == 8) { return get(12); }
    else if (pin == 9) { return get(13); }
	else { return false; }
}

void pinduinoPins::resetJ122(int pin) {
    if      (pin == 1) { resetPin(6); }
    else if (pin == 2) { resetPin(7); }
    else if (pin == 3) { resetPin(8); }
    else if (pin == 4) { resetPin(9); }
    else if (pin == 5) { resetPin(10); }
    else if (pin == 6) { resetPin(11); }
    // 7 is key
    else if (pin == 8) { resetPin(12); }
    else if (pin == 9) { resetPin(13); }
}

bool pinduinoPins::J123(int pin) {
    if      (pin == 1) { return get(6); }
    // 2 is key
    else if (pin == 3) { return get(7); }
    else if (pin == 4) { return get(8); }
    else if (pin == 5) { return get(9); }
    else { return false; }
}

void pinduinoPins::resetJ124(int pin) {
    if      (pin == 1) { resetPin(6); }
    else if (pin == 2) { resetPin(7); }
    else if (pin == 3) { resetPin(8); }
    // 4 is key
    else if (pin == 5) { resetPin(9); }
}

bool pinduinoPins::J124(int pin) {
    if      (pin == 1) { return get(6); }
    else if (pin == 2) { return get(7); }
    else if (pin == 3) { return get(8); }
    // 4 is key
    else if (pin == 5) { return get(9); }
    else { return false; }
}

void pinduinoPins::resetJ123(int pin) {
    if      (pin == 1) { resetPin(6); }
        // 2 is key
    else if (pin == 3) { resetPin(7); }
    else if (pin == 4) { resetPin(8); }
    else if (pin == 5) { resetPin(9); }
}

bool pinduinoPins::J125(int pin) {
    if      (pin == 1) { return get(14); }
    else if (pin == 2) { return get(15); }
    else if (pin == 3) { return get(16); }
    // 4 is key
    else if (pin == 5) { return get(17); }
    else if (pin == 6) { return get(18); }
    else if (pin == 7) { return get(19); }
    else if (pin == 8) { return get(20); }
    else if (pin == 9) { return get(21); }
    else { return false; }
}

void pinduinoPins::resetJ125(int pin) {
    if      (pin == 1) { resetPin(14); }
    else if (pin == 2) { resetPin(15); }
    else if (pin == 3) { resetPin(16); }
    // 4 is key
    else if (pin == 5) { resetPin(17); }
    else if (pin == 6) { resetPin(18); }
    else if (pin == 7) { resetPin(19); }
    else if (pin == 8) { resetPin(20); }
    else if (pin == 9) { resetPin(21); }
}

bool pinduinoPins::J126(int pin) {
    if      (pin == 1)  { return get(14); }
    else if (pin == 2)  { return get(15); }
    else if (pin == 3)  { return get(16); }
    else if (pin == 4)  { return get(17); }
    else if (pin == 5)  { return get(18); }
    else if (pin == 6)  { return get(19); }
    else if (pin == 7)  { return get(20); }
    else if (pin == 8)  { return get(21); }
    // 9 is key
    else if (pin == 10) { return get(22); }
    else if (pin == 11) { return get(23); }
    else if (pin == 12) { return get(24); }
    else if (pin == 13) { return get(25); }
    else { return false; }
}

void pinduinoPins::resetJ126(int pin) {
    if      (pin == 1)  { resetPin(14); }
    else if (pin == 2)  { resetPin(15); }
    else if (pin == 3)  { resetPin(16); }
    else if (pin == 4)  { resetPin(17); }
    else if (pin == 5)  { resetPin(18); }
    else if (pin == 6)  { resetPin(19); }
    else if (pin == 7)  { resetPin(20); }
    else if (pin == 8)  { resetPin(21); }
    // 9 is key
    else if (pin == 10) { resetPin(22); }
    else if (pin == 11) { resetPin(23); }
    else if (pin == 12) { resetPin(24); }
    else if (pin == 13) { resetPin(25); }
}

bool pinduinoPins::J9 (int pin) {
    return false;
}

void pinduinoPins::resetJ9 (int pin) {
}

bool pinduinoPins::J110 (int pin) {
    return false;
}

void pinduinoPins::resetJ110 (int pin) {
}

bool pinduinoPins::J111 (int pin) {
    return false;
}

void pinduinoPins::resetJ111 (int pin) {
}

bool pinduinoPins::P12 (int pin) {
    return false;
}

void pinduinoPins::resetP12 (int pin) {
}

bool pinduinoPins::P11 (int pin) {
    return false;
}

void pinduinoPins::resetP11 (int pin) {
}

int pinduinoPins::numPins() {
	return _numPins;
}

//helps with debugging
void pinduinoPins::print() {
	for (int i = 0; i < _numPins; i++) {
		Serial.print(_pinStates[i]);    
		Serial.print(" ");
	}
	Serial.println();
}

void pinduinoPins::update()
{
	for (int i = 0; i < _numPins; i++) {
	    if (_pins[i] != -1) {
            _pinStates[i] |= digitalRead(_pins[i]);
        }
	}
}
