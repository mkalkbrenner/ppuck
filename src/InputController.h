#ifndef INPUTCONTROLLER_h
#define INPUTCONTROLLER_h

#include <Arduino.h>

#include "Solenoids.h"
#include "SwitchMatrix.h"
#include "LightMatrix.h"
#include "PIN2DMD.h"
#include "PUPComLink.h"
#include "EventDispatcher.h"
#include "EventListener.h"

class InputController {
public:
    InputController(String controllerType);

    Solenoids *solenoids();

    SwitchMatrix *switchMatrix();

    LightMatrix *lightMatrix();

    PIN2DMD *pin2Dmd();

    PUPComLink *pupComLink();

    EventDispatcher *eventDispatcher();

private:
    Solenoids *_solenoids;
    SwitchMatrix *_switchMatrix;
    LightMatrix *_lightMatrix;
    PIN2DMD *_pin2Dmd;
    PUPComLink *_pupComLink;
    EventDispatcher *_eventDispatcher;
};

#endif
