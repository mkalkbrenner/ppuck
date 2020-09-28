#include "PUPSerial.h"

PUPSerial::PUPSerial() {
    Serial2.begin(115200, SERIAL_8N1);
}

void PUPSerial::postEvent(char msgtype, word msgvalue) {
    write(PUP_POST_EVENT_COMMAND, msgtype, msgvalue);
}

void PUPSerial::customCommand(char msgtype, word msgvalue) {
    write(PUP_CUSTOM_COMMAND, msgtype, msgvalue);
}

int PUPSerial::available() {
    return Serial2.available();
}

byte PUPSerial::read() {
    return Serial2.read();
}

void PUPSerial::write(byte command, char msgtype, word msgvalue) {
    byte msg[6];

    msg[0] = command;
    msg[1] = msgtype;
    msg[2] = highByte(msgvalue);
    msg[3] = lowByte(msgvalue);
    // two steps for the checksum:
    // 1. bitwise OR of MSGTYPE and HighByte(MSGVALUE)
    // 2. bitwise XOR of the result of 1 and LowByte(MSGVALUE)
    msg[4] = (msg[1] | msg[2]) ^ msg[3];
    msg[5] = PUP_EOF;

    Serial2.write(msg, 6);
}
