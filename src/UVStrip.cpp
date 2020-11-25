#include "UVStrip.h"

// see https://forum.arduino.cc/index.php?topic=398610.0
UVStrip* UVStrip::uvStripInstance = NULL;

void UVStrip::setBrightness(byte brightness)
{
    if (brightness > 255) {
        brightness = 255;
    }
    else if (brightness < 0) {
        brightness = 0;
    }

    if (brightness == 0) {
        digitalWrite(_pin, 0);
    }
    else {
        analogWrite(_pin, brightness);
    }

    _brightness = brightness;
}

void UVStrip::fadeIn(long time)
{
    fadeIn(time, 255);
}

void UVStrip::fadeIn(long time, byte brightness)
{
    setBrightness(0);
    Task((long) (time / brightness), brightness, &UVStrip::_fadeIn, _scheduler);
}

void UVStrip::fadeOut(long time)
{
    Task((long) (time / _brightness), _brightness +  1, &UVStrip::_fadeOut, _scheduler);
}

void UVStrip::_fadeIn() {
    uvStripInstance->setBrightness(uvStripInstance->_brightness + 1);
}

void UVStrip::_fadeOut() {
    uvStripInstance->setBrightness(uvStripInstance->_brightness - 1);
}
