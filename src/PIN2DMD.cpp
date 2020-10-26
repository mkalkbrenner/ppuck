#include "PIN2DMD.h"

PIN2DMD::PIN2DMD(EventDispatcher* eD) {
    eventDispatcher = eD;
    reset();
}

void PIN2DMD::setSerial(HardwareSerial &reference) {
    hwSerial = &reference;
    ((HardwareSerial*) hwSerial)->begin(57600);
}

void PIN2DMD::reset() {
    for (int i = 0; i < PIN2DMD_EVENT_CACHE_SIZE; i++) {
        eventCache[i] = 0;
    }
    eventCacheCounter = 0;
}

bool PIN2DMD::get(byte device, byte command) {
    uint16_t event = word(device, command);
    for (int i = 0; i < PIN2DMD_EVENT_CACHE_SIZE; i++) {
        if (eventCache[i] == event) {
            return true;
        }
    }
    return false;
}

void PIN2DMD::update() {
    if (hwSerial->available() > 2) {
        byte deviceByte = hwSerial->read();
        if (deviceByte != 0) {
            byte eventByte = hwSerial->read();
            if (eventByte != 0) {
                byte nullByte = hwSerial->read();
                if (nullByte == 0) {
                    eventCache[eventCacheCounter] = word(deviceByte - 100, eventByte);

                    eventDispatcher->dispatch(EVENT_SOURCE_DMD, eventCache[eventCacheCounter]);

                    if (++eventCacheCounter > PIN2DMD_EVENT_CACHE_SIZE) {
                        eventCacheCounter = 0;
                    }
                }
            }
        }
    }
}

void PIN2DMD::print() {
    Serial.println("PIN2DMD events");
    for (int i = 0; i < PIN2DMD_EVENT_CACHE_SIZE; i++) {
        Serial.print("device: "); Serial.print(highByte(eventCache[i]));
        Serial.print(" command: "); Serial.println(lowByte(eventCache[i]));
    }
}
