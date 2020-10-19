#include "PUPSerial.h"

PUPSerial::PUPSerial() {
}

void PUPSerial::setSerial(HardwareSerial &reference) {
    hwSerial = &reference;
    ((HardwareSerial*) hwSerial)->begin(115200, SERIAL_8N1);
}


void PUPSerial::postEvent(char msgtype, int msgindex, int msgvalue) {
    write(PUP_POST_EVENT_COMMAND, msgtype, word(msgindex), word(msgvalue));
}

void PUPSerial::customCommand(char msgtype, int msgindex, int msgvalue) {
    write(PUP_CUSTOM_COMMAND, msgtype, word(msgindex), word(msgvalue));
}

void PUPSerial::setVolume(int volume) {
    write(PUP_CUSTOM_COMMAND, PUP_CUSTOM_VOLUME, word(0), word(volume));
}

void PUPSerial::startBatch(int id) {
    write(PUP_CUSTOM_COMMAND, PUP_CUSTOM_BATCH, word(0), word(id));
}

void PUPSerial::restart() {
    write(PUP_CUSTOM_COMMAND, PUP_CUSTOM_RESTART, word(0), word(1));
}

void PUPSerial::shutdown() {
    write(PUP_CUSTOM_COMMAND, PUP_CUSTOM_SHUTDOWN, word(0), word(1));
}

int PUPSerial::available() {
    return hwSerial->available();
}

byte PUPSerial::read() {
    return hwSerial->read();
}

void PUPSerial::write(byte command, char msgtype, word msgindex, word msgvalue) {
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
