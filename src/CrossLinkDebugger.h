/*
  CrossLinkDebugger.h
  Created by Markus Kalkbrenner, 2020.

  Play more pinball!
*/

#ifndef CROSSLINKDEBUGGER_h
#define CROSSLINKDEBUGGER_h

#include <Arduino.h>
#include "EventListener.h"

class CrossLinkDebugger : public EventListener {
public:
    CrossLinkDebugger();

    void setSerial(HardwareSerial &reference);

    void handleEvent(char sourceId, word eventId);

protected:
    Stream *hwSerial;
};

#endif
