/*
  SwitchMatrix.h - Library for pinduino shield for Arduinos.
  Created by Markus Kalkbrenner, 2020.

  Play more pinball!
*/

#ifndef SwitchMatrix_h
#define SwitchMatrix_h

#include <Arduino.h>
#include "Matrix.h"

class SwitchMatrix : public Matrix {
public:
    SwitchMatrix(EventDispatcher* eD) : Matrix(eD) {
        switchMatrixInstance = this;

        pinMode(2, INPUT);
        pinMode(3, INPUT);
        pinMode(4, INPUT);

        pinMode(22, INPUT);
        pinMode(23, INPUT);
        pinMode(24, INPUT);
        pinMode(25, INPUT);
        pinMode(26, INPUT);
        pinMode(27, INPUT);
        pinMode(28, INPUT);
        pinMode(29, INPUT);
    }

    void start();

    void stop();

    static void _readRow();

    volatile byte columnCounter = -1;

protected:
    char eventSource = EVENT_SOURCE_SWITCH;

private:
    static SwitchMatrix* switchMatrixInstance;
};

#endif
