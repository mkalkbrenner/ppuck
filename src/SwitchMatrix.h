#ifndef SwitchMatrix_h
#define SwitchMatrix_h

#include <Arduino.h>

class SwitchMatrix {
public:
    SwitchMatrix();

    bool get(int row, int column);

    void reset(int row, int column);

    void reset();

    void print();

    void setLastRowToRead(int lastRowToRead);

    static void _readFirstRow();
    static void _readNextRow();

private:
    volatile static int lastRowToRead;
    volatile static int rowCounter;
    volatile static byte rows[8];
};

#endif
