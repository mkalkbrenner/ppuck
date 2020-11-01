/*
  LightMatrix.h
  Created by Markus Kalkbrenner, 2020.
  Derived from afterglow: 2018-2019 Christoph Schmid

  Play more pinball!
*/

#ifndef LightMatrix_h
#define LightMatrix_h

#include <Arduino.h>
#include <TimerOne.h>
#include "Matrix.h"

// Number of consistent data samples required for matrix update
#define SINGLE_UPDATE_CONS 2

// original matrix update interval [us]
#define ORIG_INT (2000)

// local time interval, config A [us]
#define TTAG_INT_A (250)

// cycles per original interval, config A
#define ORIG_CYCLES_A (ORIG_INT / TTAG_INT_A)

// local time interval, config B [us]
#define TTAG_INT_B (500)

// cycles per original interval, config B
#define ORIG_CYCLES_B (ORIG_INT / TTAG_INT_B)

class LightMatrix : public Matrix {
public:
    LightMatrix(EventDispatcher* eD) : Matrix(eD) {
        lightMatrixInstance = this;

        pinMode(5, INPUT);
        pinMode(6, OUTPUT);
        pinMode(7, OUTPUT);

        Timer1.initialize(TTAG_INT_A);
    }

    void start();

    void stop();

    static void _readRow();

    uint16_t sampleInput();

    bool updateValid(byte inColMask, byte inRowMask);

    void updateCol(uint32_t col, byte rowMask);

    // remember the last column and row samples
    volatile byte sLastColMask = 0;
    volatile byte sLastRowMask = 0;

protected:
    char eventSource = EVENT_SOURCE_LIGHT;

private:
    static LightMatrix* lightMatrixInstance;
};

#endif
