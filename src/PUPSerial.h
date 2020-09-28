#ifndef PUPSERIAL_h
#define PUPSERIAL_h

#include <Arduino.h>

#define PUP_POST_EVENT_COMMAND 80 // "P"
#define PUP_CUSTOM_COMMAND 67 // "C"
#define PUP_EOF 13
#define PUP_TYPE_DMD 68 // "D"
#define PUP_TYPE_SWITCH 87 // "W"

class PUPSerial {
public:
    PUPSerial();

    void postEvent(char msgtype, word msgvalue);

    void customCommand(char msgtype, word msgvalue);

    int available();

    byte read();

protected:
    void write(byte command, char msgtype, word msgvalue);

};

#endif
