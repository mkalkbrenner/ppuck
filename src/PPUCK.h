#ifndef PPUCK_h
#define PPUCK_h

#include <Arduino.h>

#include "RGBStrip.h"
#include "AddressableStrip.h"
#include "AddressableMatrix.h"
#include "Solenoids.h"
#include "DataPort.h"
#include "SwitchMatrix.h"
#include "LightMatrix.h"
#include "PIN2DMD.h"
#include "PUPComLink.h"
#include "EventDispatcher.h"
#include "EventListener.h"

class PPUCK {
protected:

public:
    PPUCK(String controllerType);

    Solenoids *solenoids();

    SwitchMatrix *switchMatrix();

    LightMatrix *lightMatrix();

    PIN2DMD *pin2Dmd();

    PUPComLink *pupComLink();

    EventDispatcher *eventDispatcher();

    //functions for controlling 12V RGB strips
    RGBStrip *rgbLED1();

    RGBStrip *rgbLED2();

    RGBStrip *rgbLED3();

    RGBStrip *rgbLED4();

    //functions for controlling 5V Addressable LED strips
    AddressableStrip *adrLED1();

    AddressableStrip *adrLED2();

    AddressableStrip *adrLED3();

    AddressableStrip *adrLED4();

    //functions for creating 5V Addressable LED matrices
    AddressableMatrix *adrMatrix(AddressableStrip *adr, int col, int row, int start);

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

    void
    chaseAllAdr2RGBFromPoint(int pos, float r1, float g1, float b1, float r2, float g2, float b2, int span, int time);

    void testRGBStrip(RGBStrip *strip);

    void testRGBStrip1();

    void testRGBStrip2();

    void testRGBStrip3();

    void testRGBStrip4();

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
    //internal object for monitoring pinball machine states
    Solenoids *_solenoids;
    SwitchMatrix *_switchMatrix;
    LightMatrix *_lightMatrix;
    PIN2DMD *_pin2Dmd;
    PUPComLink *_pupComLink;
    EventDispatcher *_eventDispatcher;

    //internal objects for RGB strip control`
    RGBStrip *RGB1;
    RGBStrip *RGB2;
    RGBStrip *RGB3;
    RGBStrip *RGB4;

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
