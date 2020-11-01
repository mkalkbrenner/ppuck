/*
  Matrix.h
  Created by Markus Kalkbrenner, 2020.

  Play more pinball!
*/

#ifndef Matrix_h
#define Matrix_h

#include <Arduino.h>
#include "EventDispatcher.h"

#ifndef MAX_FIELDS_REGISTERED
#define MAX_FIELDS_REGISTERED 72
#endif

#ifndef NUM_COLS
#define NUM_COLS 9
#endif

class Matrix {
public:
    Matrix(EventDispatcher* eD);

    virtual void start() = 0;

    virtual void stop() = 0;

    void update();

    void print();

    void setLastColToRead(byte lastColToRead);

    void registerFieldAsEvent(byte row, byte column, byte number);

    void registerAllFieldsAsEvent(String pinballType);

    static void _readRow() {}

    volatile byte lastColToRead;
    volatile byte rows[NUM_COLS];

protected:
    EventDispatcher* eventDispatcher;

    char eventSource;

    byte previousRows[NUM_COLS];

    int registeredFieldsCounter = -1;
    word registeredFieldRowCol[MAX_FIELDS_REGISTERED];
    byte registeredFieldNum[MAX_FIELDS_REGISTERED];
};

#endif
