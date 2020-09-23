#include "SwitchMatrix.h"

SwitchMatrix::SwitchMatrix(int lastColToRead, int referenceCol = -1) {
	this->lastColToRead = --lastColToRead;
    this->referenceCol = --referenceCol;
	col = 0;
	rowIndex = 0;
	referenceColBuffer = B00000000;
	rowsBufferReady = false;
    for (int i = 0; i < lastColToRead; i++) {
    	for (int k = 0; k < 2; k++) {
            rows[k][i] = B00000000;
        }
        rowsBuffer[i] = B00000000;
	}
}

void SwitchMatrix::reset() {
    for (int i = 0; i < lastColToRead; i++) {
        rowsBuffer[i] = B00000000;
    }
    rowsBufferReady = false;
}

bool SwitchMatrix::get(int column, int row) {
    return rowsBuffer[column] | byte(pow(2, row - 1));
}

void SwitchMatrix::readSwitches() {
    // Read row return at PIN 22 - 29 and invert the active low signal.
	rows[rowIndex][col] = PINA ^ B11111111;

	if (++col >= lastColToRead) {
        noInterrupts();

        // row index for row to compare
        int row = (rowIndex == 1 ? 0 : 1);

        for (int i = 0; i < lastColToRead; i++) {
            if (rows[rowIndex][i] != rows[row][i]) {
                if (i == referenceCol) {
                    // Reference column is not expected to change frequently. Usually the column that contains the ball
                    // store switches. Sometimes we get false reads. To mitigate these we ignore the first change of the
                    // reference column, reset the reads and skip the following columns.
                    referenceColBuffer = rows[rowIndex][i];
                    if (rows[rowIndex][i] != referenceColBuffer) {
                        for (int k = 0; k <= lastColToRead; k++) {
                            rows[rowIndex][k] = rows[row][k];
                        }
                        dumpSwitches = false;
                        i = lastColToRead;
                    }
                    else {
                        dumpSwitches = true;
                    }
                }
                else {
                    dumpSwitches = true;
                }
            }

        }

        if (dumpSwitches) {
            for (int i = 0; i <= lastColToRead; i++) {
                rowsBuffer[i] |= rows[rowIndex][i];
            }
            rowsBufferReady = true;
        }
        col = 0;
        rowIndex = row;

        interrupts();
    }
}

void SwitchMatrix::dump() {
    if (dumpSwitches) {
        Serial.println("  8 7 6 5 4 3 2 1");
        for (int i = 0; i <= lastColToRead; i++) {
            Serial.print(i + 1);
            for (byte mask = 0x80; mask; mask >>= 1) {
                Serial.print(mask & rowsBuffer[i] ? " *" : " -");
            }
            Serial.println();
        }
        dumpSwitches = false;
    }
}

SwitchMatrix::~SwitchMatrix() {
}

