/*
  PUPSerial.h - Library for pinduino shield for Arduinos.
  Created by Markus Kalkbrenner, 2020.

  Play more pinball!
*/

#ifndef PUPSERIAL_h
#define PUPSERIAL_h

#include <Arduino.h>

#define PUP_POST_EVENT_COMMAND 80 // "P"
#define PUP_CUSTOM_COMMAND 67 // "C"
#define PUP_EOF 13
#define PUP_TYPE_DMD 68 // "D"
#define PUP_TYPE_SWITCH 87 // "W"
#define PUP_VALUE_ON 1
#define PUP_CUSTOM_VOLUME 86 // "V"
#define PUP_CUSTOM_BATCH 66 // "B"
#define PUP_CUSTOM_RESTART 82 // "R"
#define PUP_CUSTOM_SHUTDOWN 83 // "S"

class PUPSerial {
public:
    PUPSerial();

    void setSerial(HardwareSerial &reference);

    void postEvent(char msgtype, int msgindex, int msgvalue);

    void customCommand(char msgtype, int msgindex, int msgvalue);

    void setVolume(int volume);

    /**
     * Starts "id".bat in the "pinupsystem\launch" folder
     */
    void startBatch(int id);

    void restart();

    void shutdown();

    int available();

    byte read();

protected:
    void write(byte command, char msgtype, word msgindex, word msgvalue);

    Stream *hwSerial;
};

#endif
