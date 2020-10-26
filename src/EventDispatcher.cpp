#include "EventDispatcher.h"

EventDispatcher::EventDispatcher() {
}

void EventDispatcher::setCrossLinkSerial(HardwareSerial &reference) {
    hwSerial = &reference;
    ((HardwareSerial*) hwSerial)->begin(115200);
    crossLink = true;
}

void EventDispatcher::addListener(EventListener* eventListener) {
    addListener(eventListener, EVENT_SOURCE_ANY);
}

void EventDispatcher::addListener(EventListener* eventListener, char sourceId) {
    if (numListeners < (MAX_EVENT_LISTENERS - 1)) {
        eventListeners[++numListeners] = eventListener;
        eventListenerFilters[numListeners] = sourceId;
    }
}

void EventDispatcher::dispatch(char sourceId, word eventId) {
    for (int i = 0; i <= numListeners; i++) {
        if (sourceId == eventListenerFilters[i] || EVENT_SOURCE_ANY == eventListenerFilters[i]) {
            eventListeners[i]->handleEvent(sourceId, eventId);
        }

        if (crossLink) {
            byte msg[3];

            msg[0] = (byte) sourceId;
            msg[1] = highByte(eventId);
            msg[2] = lowByte(eventId);

            hwSerial->write(msg, 3);
        }
    }
}

void EventDispatcher::dispatchInternal(char sourceId, word eventId) {
    for (int i = 0; i <= numListeners; i++) {
        if (sourceId == eventListenerFilters[i] || '*' == eventListenerFilters[i]) {
            eventListeners[i]->handleEvent(sourceId, eventId);
        }
    }
}

void EventDispatcher::update() {
    if (crossLink && hwSerial->available() > 3) {
        byte sourceId = hwSerial->read();
        if (sourceId != 0) {
            byte eventIdHighByte = hwSerial->read();
            if (eventIdHighByte != 0) {
                byte eventIdLowByte = hwSerial->read();
                if (eventIdLowByte != 0) {
                    byte nullByte = hwSerial->read();
                    if (nullByte == 0) {
                        dispatch((char) sourceId, word(eventIdHighByte, eventIdLowByte));
                    }
                }
            }
        }
    }
}
