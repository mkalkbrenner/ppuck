#ifndef PIN2DMD_h
#define PIN2DMD_h

#include <Arduino.h>

#define PIN2DMD_EVENT_CACHE_SIZE 10

class PIN2DMD {
public:
    PIN2DMD();

    bool get(byte device, byte command);

    void reset(byte device, byte command);

    void reset();

    void print();

    void update();

    void forward(bool enable);

private:
    uint16_t eventCache[PIN2DMD_EVENT_CACHE_SIZE];
    int eventCacheCounter;

    bool forwardEnabled;
};

#endif
