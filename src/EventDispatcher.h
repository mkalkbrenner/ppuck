/*
  EventDispatcher.h - Library for pinduino shield for Arduinos.
  Created by Markus Kalkbrenner, 2020.

  Play more pinball!
*/

#ifndef EVENTDISPATCHER_h
#define EVENTDISPATCHER_h

#include <Arduino.h>
#include "EventListener.h"

#ifndef MAX_EVENT_LISTENERS
#define MAX_EVENT_LISTENERS 5
#endif

#define EVENT_SOURCE_ANY 42 // "*"
#define EVENT_SOURCE_DMD 68 // "D"
#define EVENT_SOURCE_SWITCH 87 // "W"

class EventDispatcher {
public:
    EventDispatcher();

    void setCrossLinkSerial(HardwareSerial &reference);

    void addListener(EventListener* eventListener, char sourceId);

    void addListener(EventListener* eventListener);

    void dispatch(char sourceId, word eventId);

    void update();

private:
    void dispatchInternal(char sourceId, word eventId);

    EventListener* eventListeners[MAX_EVENT_LISTENERS];
    char eventListenerFilters[MAX_EVENT_LISTENERS];
    int numListeners = -1;

    bool crossLink = false;
    Stream* hwSerial;
};

#endif
