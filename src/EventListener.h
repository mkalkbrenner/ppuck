/*
  EventListener.h - Library for pinduino shield for Arduinos.
  Created by Markus Kalkbrenner, 2020.

  Play more pinball!
*/

#ifndef EVENTLISTENER_h
#define EVENTLISTENER_h

class EventListener {
public:
    virtual void handleEvent(char sourceId, word eventId) = 0;
};

#endif
