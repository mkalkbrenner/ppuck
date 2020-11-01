#include "SwitchMatrix.h"

// see https://forum.arduino.cc/index.php?topic=398610.0
SwitchMatrix* SwitchMatrix::switchMatrixInstance = NULL;

void SwitchMatrix::start() {
    attachInterrupt(digitalPinToInterrupt(2), SwitchMatrix::_readRow, RISING);
    attachInterrupt(digitalPinToInterrupt(3), SwitchMatrix::_readRow, RISING);
}

void SwitchMatrix::stop() {
    detachInterrupt(digitalPinToInterrupt(2));
    detachInterrupt(digitalPinToInterrupt(3));
}

void SwitchMatrix::_readRow() {
    if (!digitalRead(4)) {
        switchMatrixInstance->columnCounter = 0;
    }

    if (switchMatrixInstance->columnCounter >= 0 &&
            switchMatrixInstance->columnCounter <= switchMatrixInstance->lastColToRead
    ) {
        // Read row return at PIN 22 - 29.
        switchMatrixInstance->rows[switchMatrixInstance->columnCounter] |= PINA ^ B11111111;
        //matrixInstance->rows[matrixInstance->columnCounter] |= PINA;
        switchMatrixInstance->columnCounter++;
    }
}
