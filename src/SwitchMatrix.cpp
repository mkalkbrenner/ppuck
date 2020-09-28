#include "SwitchMatrix.h"

// see https://forum.arduino.cc/index.php?topic=398610.0
SwitchMatrix* SwitchMatrix::switchMatrixInstance = NULL;

SwitchMatrix::SwitchMatrix() {
    switchMatrixInstance = this;

    setLastRowToRead(8);
	reset();

    blockCounter = 0;
    for (int i = 0; i < MAX_SWITCHES_BLOCKED; i++) {
        blocked[i] = 0;
        blockedMs[i] = 0L;
    }

    attachInterrupt(digitalPinToInterrupt(2), SwitchMatrix::_readFirstRow, FALLING);
    attachInterrupt(digitalPinToInterrupt(3), SwitchMatrix::_readNextRow, FALLING);
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

bool SwitchMatrix::getOnce(int row, int column, int ms) {
    word row_col = word(row, column);
    unsigned long now = millis();
    for (int i = 0; i < MAX_SWITCHES_BLOCKED; i++) {
        if (blocked[i] == row_col) {
            if (blockedMs[i] > now) {
                return false;
            }
            else {
                blocked[i] = 0;
                blockedMs[i] = 0L;
                break;
            }
        }
    }

    bool state = get(row, column);

    if (state) {
        if (++blockCounter > MAX_SWITCHES_BLOCKED) {
            blockCounter = 0;
        }
        blocked[blockCounter] = row_col;
        blockedMs[blockCounter] = now + ms;
    }

    return state;
}

void SwitchMatrix::_readFirstRow() {
    // Read row return at PIN 22 - 29.
    switchMatrixInstance->rows[0] |= PINA;
    switchMatrixInstance->rowCounter = 1;
}

void SwitchMatrix::_readNextRow() {
    if (switchMatrixInstance->rowCounter > 0 && switchMatrixInstance->rowCounter <= switchMatrixInstance->lastRowToRead) {
        // Read row return at PIN 22 - 29.
        //self->rows[col++] |= PINA ^ B11111111;
        switchMatrixInstance->rows[switchMatrixInstance->rowCounter++] |= PINA;
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
