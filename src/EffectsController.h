#ifndef EFFECTSCONTROLLER_h
#define EFFECTSCONTROLLER_h

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>

#include "AddressableStrip.h"
#include "DataPort.h"
#include "EventDispatcher.h"
#include "EventListener.h"
#include "UVStrip.h"
#include "CrossLinkDebugger.h"

class EffectsController {

public:
    EffectsController(String controllerType);

    EventDispatcher *eventDispatcher();

    CrossLinkDebugger *crossLinkDebugger();

    //functions for controlling 12V RGB strips
    UVStrip *uv();

    //functions for controlling 5V Addressable LED strips
    AddressableStrip *adrLED1();

    AddressableStrip *adrLED2();

    AddressableStrip *adrLED3();

    AddressableStrip *adrLED4();

    //Functions for controlling output ports
    DataPort *port1();

    DataPort *port2();

    DataPort *port3();

    DataPort *port4();

    //functions that affect multiple AddressableStrips simultaneously
    // color all strips
    void colorAllAdrRGB(int r, int g, int b);

    void colorAllAdr(String color);

    //fade out all strips
    void fadeOutAllAdr(float time);

    //fade in all strips (note, colors on strips need to be set first using ALED1->color("red",1);)
    void fadeInAllAdr(String color, float time);

    void fadeInAllAdrRGB(int r, int g, int b, float time);

    void fadeAllAdrRGB2RGB(float r1, float g1, float b1, float r2, float g2, float b2, float time);

    void fadeAllAdrColor2Color(String color1, String color2, float time);

    void chaseAllAdr2RGB(float r1, float g1, float b1, float r2, float g2, float b2, float span, int time, int dir);

    void chaseAllAdr2Color(String color1, String color2, float span, int time, int dir);

    void chaseAllAdr2RGBFromPoint(int pos, float r1, float g1, float b1, float r2, float g2, float b2, int span, int time);

    void testSpeakerAdrLED(AddressableStrip *strip);

    void testSpeakerAdrLED1();

    void testAdrLED(AddressableStrip *strip);

    void testAdrLED1();

    void testAdrLED2();

    void testAdrLED3();

    void testAdrLED4();

    void testAdrLEDAlpha(AddressableStrip *strip);

    void testAdrLED1Alpha();

    void testAdrLED2Alpha();

    void testAdrLED3Alpha();

    void testAdrLED4Alpha();

private:
    EventDispatcher *_eventDispatcher;
    Scheduler *_scheduler;
    CrossLinkDebugger *_crossLinkDebugger;

    //internal objects for RGB strip control`
    UVStrip *UV;

    //internal objects for AddressableStrip control
    AddressableStrip *ALED1;
    AddressableStrip *ALED2;
    AddressableStrip *ALED3;
    AddressableStrip *ALED4;

    //internal objects for control output ports (set high and low for transistor/relay control)
    DataPort *DATAPORT1;
    DataPort *DATAPORT2;
    DataPort *DATAPORT3;
    DataPort *DATAPORT4;

    void init(int aledNum1, int aledNum2, int aledNum3, int aledNum4, String arduinoType);
};

#endif
