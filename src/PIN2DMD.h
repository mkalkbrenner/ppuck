/*
  PIN2DMD.h - Library for pinduino shield for Arduinos.
  Created by Markus Kalkbrenner, 2020.

  Play more pinball!
*/

#ifndef PIN2DMD_h
#define PIN2DMD_h

#include <Arduino.h>
#include "PUPSerial.h"

#define PIN2DMD_EVENT_CACHE_SIZE 10

class PIN2DMD {
public:
    PIN2DMD();

    void setSerial(HardwareSerial &reference);

    bool get(byte device, byte command);

    void reset(byte device, byte command);

    void reset();

    void print();

    void update();

    void forwardToPUP(PUPSerial *pupSerial);

private:
    uint16_t eventCache[PIN2DMD_EVENT_CACHE_SIZE];
    int eventCacheCounter;

    bool forwardEnabled;
    PUPSerial *pupSerial;

    Stream *hwSerial;

};

#endif
