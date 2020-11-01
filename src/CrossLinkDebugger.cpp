#include "CrossLinkDebugger.h"

CrossLinkDebugger::CrossLinkDebugger() {
}

void CrossLinkDebugger::setSerial(HardwareSerial &reference) {
    hwSerial = &reference;
    ((HardwareSerial*) hwSerial)->begin(115200, SERIAL_8N1);
}

void CrossLinkDebugger::handleEvent(char sourceId, word eventId) {
    hwSerial->print("handleEvent: sourceId ");
    hwSerial->print(sourceId);
    hwSerial->print(", eventId ");
    hwSerial->println(eventId);
}
