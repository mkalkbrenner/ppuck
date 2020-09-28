#ifndef SwitchMatrix_h
#define SwitchMatrix_h

#include <Arduino.h>

#define MAX_SWITCHES_BLOCKED 10

class SwitchMatrix {
public:
    SwitchMatrix();

    bool get(int row, int column);

    bool getOnce(int row, int column, int ms);

    void reset(int row, int column);

    void reset();

    void print();

    void setLastRowToRead(int lastRowToRead);

    static void _readNextRow();

    volatile int lastRowToRead;
    volatile int rowCounter;
    volatile byte rows[8];

private:
    static SwitchMatrix* switchMatrixInstance;

    int blockCounter;
    word blocked[MAX_SWITCHES_BLOCKED];
    unsigned long blockedMs[MAX_SWITCHES_BLOCKED];
};

#endif
