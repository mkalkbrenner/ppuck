/*
  SwitchMatrix.h - Library for pinduino shield for Arduinos.
  Created by Markus Kalkbrenner, 2020.

  Play more pinball!
*/

#ifndef SwitchMatrix_h
#define SwitchMatrix_h

#include <Arduino.h>
#include "EventDispatcher.h"

#ifndef MAX_SWITCHES_REGISTERED
#define MAX_SWITCHES_REGISTERED 10
#endif

#define MAX_SWITCHES_BLOCKED 10

class SwitchMatrix {
public:
    SwitchMatrix(EventDispatcher* eD);

    bool get(byte row, byte column);

    bool getOnce(byte row, byte column, int ms);

    void reset(byte row, byte column);

    void reset();

    void print();

    void setLastRowToRead(byte lastRowToRead);

    void registerSwitch(byte row, byte column, byte number);

    static void _readNextRow();

    volatile byte lastRowToRead;
    volatile byte columnCounter;
    volatile byte rows[8];

private:
    static SwitchMatrix* switchMatrixInstance;
    EventDispatcher* eventDispatcher;

    int blockCounter;
    word blocked[MAX_SWITCHES_BLOCKED];
    unsigned long blockedMs[MAX_SWITCHES_BLOCKED];

    int registeredSwitchCounter = -1;
    word registeredSwitchRowCol[MAX_SWITCHES_REGISTERED];
    byte registeredSwitchNum[MAX_SWITCHES_REGISTERED];
};

#endif
