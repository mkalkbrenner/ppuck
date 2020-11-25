#include "InputController.h"

InputController::InputController(String controllerType) {
    _eventDispatcher = new EventDispatcher();
    _solenoids = new Solenoids(controllerType, _eventDispatcher);

    if (controllerType == "PPUC-Arduino-0.1.0") {
        _switchMatrix = new SwitchMatrix(_eventDispatcher);
        _lightMatrix = new LightMatrix(_eventDispatcher);
        _pin2Dmd = new PIN2DMD(_eventDispatcher);
        _pupComLink = new PUPComLink();
    } else {
        Serial.print("Unsupported Input Controller: ");
        Serial.println(controllerType);
    }
}

Solenoids *InputController::solenoids() {
    return _solenoids;
}

SwitchMatrix *InputController::switchMatrix() {
    return _switchMatrix;
}

LightMatrix *InputController::lightMatrix() {
    return _lightMatrix;
}

PIN2DMD *InputController::pin2Dmd() {
    return _pin2Dmd;
}

PUPComLink *InputController::pupComLink() {
    return _pupComLink;
}

EventDispatcher *InputController::eventDispatcher() {
    return _eventDispatcher;
}
