#ifndef UVStrip_h
#define UVStrip_h

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>

class UVStrip
{
public:
    //Constructor
    UVStrip(byte pin, Scheduler* scheduler) {
        uvStripInstance = this;

        _pin = pin;
        _scheduler = scheduler;

        pinMode(_pin, OUTPUT);
        setBrightness(0);
    }

    void setBrightness(byte brightness);

    void fadeIn(long time);
    void fadeIn(long time, byte brightness);
    void fadeOut(long time);

    static void _fadeIn();
    static void _fadeOut();

    byte _brightness;

private:
    Scheduler *_scheduler;
    byte _pin;

    static UVStrip* uvStripInstance;

};

#endif

