#include "SwitchMatrix.h"

SwitchMatrix::SwitchMatrix() {
    setLastRowToRead(8);
	reset();
    attachInterrupt(digitalPinToInterrupt(2), _readFirstRow, FALLING);
    attachInterrupt(digitalPinToInterrupt(3), _readNextRow, FALLING);
}

void SwitchMatrix::reset() {
    rowCounter = 0;
    for (int i = 0; i < lastRowToRead; i++) {
        rows[i] = B00000000;
    }
}

void SwitchMatrix::reset(int row, int column) {
    rows[row - 1] &= byte(pow(2, column - 1)) ^ B11111111;
}

void SwitchMatrix::setLastRowToRead(int last) {
    lastRowToRead = --last;
}

bool SwitchMatrix::get(int row, int column) {
    return rows[row - 1] | byte(pow(2, column - 1));
}

void SwitchMatrix::_readFirstRow() {
    // Read row return at PIN 22 - 29.
    rows[0] |= PINA;
    rowCounter = 1;
}

void SwitchMatrix::_readNextRow() {
    if (rowCounter > 0 && rowCounter <= lastRowToRead) {
        // Read row return at PIN 22 - 29.
        //rows[col++] |= PINA ^ B11111111;
        rows[rowCounter++] |= PINA;
    }
}

void SwitchMatrix::print() {
    Serial.println("Switch Matrix");
    Serial.println("  8 7 6 5 4 3 2 1");
    for (int i = 0; i <= lastRowToRead; i++) {
        Serial.print(i + 1);
        for (byte mask = 0x80; mask; mask >>= 1) {
            Serial.print(mask & rows[i] ? " *" : " -");
        }
        Serial.println();
    }
}
