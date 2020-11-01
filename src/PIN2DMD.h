/*
  PIN2DMD.h - Library for pinduino shield for Arduinos.
  Created by Markus Kalkbrenner, 2020.

  Play more pinball!
*/

#ifndef PIN2DMD_h
#define PIN2DMD_h

#include <Arduino.h>
#include "EventDispatcher.h"

#define PIN2DMD_EVENT_CACHE_SIZE 10

class PIN2DMD {
public:
    PIN2DMD(EventDispatcher* eD) {
        eventDispatcher = eD;
        reset();
    }

    void setSerial(HardwareSerial &reference);

    void reset();

    void print();

    void update();

private:
    EventDispatcher* eventDispatcher;

    uint16_t eventCache[PIN2DMD_EVENT_CACHE_SIZE];
    int eventCacheCounter;

    Stream *hwSerial;

};

#endif
