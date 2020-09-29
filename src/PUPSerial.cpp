#include "PUPSerial.h"

PUPSerial::PUPSerial() {
    Serial2.begin(115200, SERIAL_8N1);
}

void PUPSerial::postEvent(char msgtype, int msgindex, int msgvalue) {
    write(PUP_POST_EVENT_COMMAND, msgtype, word(msgindex), word(msgvalue));
}

void PUPSerial::customCommand(char msgtype, int msgindex, int msgvalue) {
    write(PUP_CUSTOM_COMMAND, msgtype, word(msgindex), word(msgvalue));
}

int PUPSerial::available() {
    return Serial2.available();
}

byte PUPSerial::read() {
    return Serial2.read();
}

void write(byte command, char msgtype, word msgindex, word msgvalue) {
    byte msg[8];

    msg[0] = command;
    msg[1] = msgtype;
    msg[2] = highByte(msgindex);
    msg[3] = lowByte(msgindex);
    msg[4] = highByte(msgvalue);
    msg[5] = lowByte(msgvalue);
    msg[6] = msg[0]^msg[1]^msg[2]^msg[3]^msg[4]^msg[5];
    msg[7] = PUP_EOF;

    Serial2.write(msg, 8);
}
