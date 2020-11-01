#include "Matrix.h"

Matrix::Matrix(EventDispatcher* eD) {
    eventDispatcher = eD;

    setLastColToRead(8);

    for (int i = 0; i < lastColToRead; i++) {
        rows[i] = B00000000;
        previousRows[i] = B00000000;
    }
}

void Matrix::setLastColToRead(byte last) {
    lastColToRead = last;
}

void Matrix::registerFieldAsEvent(byte row, byte column, byte number) {
    if (registeredFieldsCounter < (MAX_FIELDS_REGISTERED - 1)) {
        registeredFieldRowCol[++registeredFieldsCounter] = word(row - 1, column - 1);
        registeredFieldNum[registeredFieldsCounter] = number;
    }
}

void Matrix::registerAllFieldsAsEvent(String pinballType) {
    if (pinballType == "WPC") {
        for (byte col = 1; col <= NUM_COLS; col++) {
            for (byte row = 1; row <= 8; row++) {
                registerFieldAsEvent(row, col, col * 10 + row);
            }
        }
    }
    else if (pinballType == "DE") {
        byte light = 0;
        for (byte col = 1; col <= NUM_COLS; col++) {
            for (byte row = 1; row <= 8; row++) {
                registerFieldAsEvent(row, col, ++light);
            }
        }
    }
}

void Matrix::update() {
    for (int col = 0; col < lastColToRead; col++) {
        for (int row = 0; row < 8; row++) {
            word row_col = word(row, col);
            for (byte i = 0; i <= registeredFieldsCounter; i++) {
                if (row_col == registeredFieldRowCol[i]) {
                    byte bit = 1 << row;
                    if ((rows[col] & bit) != (previousRows[col] & bit)) {
                        eventDispatcher->dispatch(eventSource, word(registeredFieldNum[i]), rows[col] & bit);
                    }
                }
            }
        }
        previousRows[col] = rows[col];
    }
}

void Matrix::print() {
    Serial.print("Matrix "); Serial.println(eventSource);
    Serial.println("  8 7 6 5 4 3 2 1");
    for (int i = 0; i < lastColToRead; i++) {
        Serial.print(i + 1);
        for (byte mask = 0x80; mask; mask >>= 1) {
            Serial.print(mask & rows[i] ? " *" : " -");
        }
        Serial.println();
    }
}
