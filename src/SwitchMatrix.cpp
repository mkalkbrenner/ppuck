#include "SwitchMatrix.h"

// see https://forum.arduino.cc/index.php?topic=398610.0
SwitchMatrix* SwitchMatrix::switchMatrixInstance = NULL;

SwitchMatrix::SwitchMatrix() {
    switchMatrixInstance = this;

    pinMode(2, INPUT);
    pinMode(3, INPUT);

    pinMode(22, INPUT);
    pinMode(23, INPUT);
    pinMode(24, INPUT);
    pinMode(25, INPUT);
    pinMode(26, INPUT);
    pinMode(27, INPUT);
    pinMode(28, INPUT);
    pinMode(29, INPUT);

    pinMode(53, INPUT);

    setLastRowToRead(8);
	reset();

    blockCounter = 0;
    for (int i = 0; i < MAX_SWITCHES_BLOCKED; i++) {
        blocked[i] = 0;
        blockedMs[i] = 0L;
    }

    attachInterrupt(digitalPinToInterrupt(2), SwitchMatrix::_readNextRow, RISING);
    attachInterrupt(digitalPinToInterrupt(3), SwitchMatrix::_readNextRow, RISING);
}

void SwitchMatrix::reset() {
    columnCounter = -1;

    for (int i = 0; i < lastRowToRead; i++) {
        rows[i] = B00000000;
    }
}

void SwitchMatrix::reset(int row, int column) {
    rows[row - 1] &= byte(pow(2, column - 1)) ^ B11111111;
}

void SwitchMatrix::setLastRowToRead(int last) {
    lastRowToRead = last - 1;
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

void SwitchMatrix::_readNextRow() {
    if (!digitalRead(53)) {
        switchMatrixInstance->columnCounter = 0;
    }

    if (switchMatrixInstance->columnCounter >= 0 &&
        switchMatrixInstance->columnCounter <= switchMatrixInstance->lastRowToRead
    ) {
        // Read row return at PIN 22 - 29.
        switchMatrixInstance->rows[switchMatrixInstance->columnCounter] |= PINA ^ B11111111;
        //switchMatrixInstance->rows[switchMatrixInstance->columnCounter] |= PINA;
        switchMatrixInstance->columnCounter++;
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