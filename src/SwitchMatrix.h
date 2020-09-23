#ifndef PINDUINO_TNG_SWITCHMATRIX_H_
#define PINDUINO_TNG_SWITCHMATRIX_H_

#include <Arduino.h>

#define MAX_HANDLERS 20

class SwitchMatrix {
public:
    SwitchMatrix(int lastColToRead, int referenceCol);

    virtual ~SwitchMatrix();

    void readSwitches();

    bool get(int column, int row);

    void reset();

    void printbin(byte bin);

    void dump();

    int lastColToRead;
    int referenceCol;

    volatile int col;
    // 2 times 8 byte for row returns
    // 2 arrays are used to detect changes
    volatile byte rows[2][8];
    // indicates which array to use
    volatile int rowIndex;
    volatile byte referenceColBuffer;
    // 2 times 8 byte for row returns
    // 2 arrays are used to detect changes
    volatile byte rowsBuffer[8];
    volatile bool rowsBufferReady;
    volatile bool dumpSwitches;
};

#endif /* PINDUINO_TNG_SWITCHMATRIX_H_ */
