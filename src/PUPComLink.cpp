#include "PUPComLink.h"

void PUPComLink::setSerial(HardwareSerial &reference) {
    hwSerial = &reference;
    ((HardwareSerial*) hwSerial)->begin(115200, SERIAL_8N1);
}

void PUPComLink::handleEvent(char sourceId, word eventId, byte value) {
    write(PUP_POST_EVENT_COMMAND, sourceId, eventId, value);
}

void PUPComLink::postEvent(char msgtype, int msgindex, int msgvalue) {
    write(PUP_POST_EVENT_COMMAND, msgtype, word(msgindex), word(msgvalue));
}

void PUPComLink::customCommand(char msgtype, int msgindex, int msgvalue) {
    write(PUP_CUSTOM_COMMAND, msgtype, word(msgindex), word(msgvalue));
}

void PUPComLink::setVolume(int volume) {
    write(PUP_CUSTOM_COMMAND, PUP_CUSTOM_VOLUME, word(0), word(volume));
}

void PUPComLink::startBatch(int id) {
    write(PUP_CUSTOM_COMMAND, PUP_CUSTOM_BATCH, word(0), word(id));
}

void PUPComLink::restart() {
    write(PUP_CUSTOM_COMMAND, PUP_CUSTOM_RESTART, word(0), word(1));
}

void PUPComLink::shutdown() {
    write(PUP_CUSTOM_COMMAND, PUP_CUSTOM_SHUTDOWN, word(0), word(1));
}

int PUPComLink::available() {
    return hwSerial->available();
}

byte PUPComLink::read() {
    return hwSerial->read();
}

void PUPComLink::write(byte command, char msgtype, word msgindex, word msgvalue) {
    byte msg[8];

    msg[0] = command;
    msg[1] = msgtype;
    msg[2] = highByte(msgindex);
    msg[3] = lowByte(msgindex);
    msg[4] = highByte(msgvalue);
    msg[5] = lowByte(msgvalue);
    msg[6] = msg[0]^msg[1]^msg[2]^msg[3]^msg[4]^msg[5];
    msg[7] = PUP_EOF;

    hwSerial->write(msg, 8);
}
