#include "PIN2DMD.h"

PIN2DMD::PIN2DMD() {
    forwardEnabled = false;
    reset();
    Serial1.begin(57600);
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
    while (Serial1.available() > 1) {
        // read two incoming bytes
        eventCache[eventCacheCounter] = word(Serial1.read(), Serial1.read());

        if (forwardEnabled) {
            pupSerial->postEvent(PUP_TYPE_DMD, eventCache[eventCacheCounter]);
        }

        if (++eventCacheCounter > PIN2DMD_EVENT_CACHE_SIZE) {
            eventCacheCounter = 0;
        }
    }
}

void PIN2DMD::forwardToPUP(PUPSerial *pupSerial) {
    forwardEnabled = true;
    this->pupSerial = pupSerial;
}


void PIN2DMD::print() {
    Serial.println("PIN2DMD events");
    for (int i = 0; i < PIN2DMD_EVENT_CACHE_SIZE; i++) {
        Serial.print("device: "); Serial.print(highByte(eventCache[i]));
        Serial.print(" command: "); Serial.println(lowByte(eventCache[i]));
    }
}
