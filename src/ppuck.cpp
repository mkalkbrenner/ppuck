/**
 * ppuck.cpp - Library for Pinball Power-Up Controller.
 * Created by Markus Kalkbrenner, 2020.
 * Parts based on pindion by Eric Lyons and Wes Sparks, 2015.
 * Play more pinball!
 */

#include "ppuck.h"

ppuck::ppuck() {
    init(1, 1, 1, 1, "PPUC-1.0");
}

ppuck::ppuck(String arduinoType) {
    init(1, 1, 1, 1, arduinoType);
}

ppuck::ppuck(int aledNum1, String arduinoType) {
    init(aledNum1, 1, 1, 1, arduinoType);
}

ppuck::ppuck(int aledNum1, int aledNum2, String arduinoType) {
    init(aledNum1, aledNum2, 1, 1, arduinoType);
}

ppuck::ppuck(int aledNum1, int aledNum2, int aledNum3) {
    init(aledNum1, aledNum2, aledNum3, 1, "PPUC-1.0");
}

ppuck::ppuck(int aledNum1, int aledNum2, int aledNum3, String arduinoType) {
    init(aledNum1, aledNum2, aledNum3, 1, arduinoType);
}

ppuck::ppuck(int aledNum1, int aledNum2, int aledNum3, int aledNum4, String arduinoType) {
    init(aledNum1, aledNum2, aledNum3, aledNum4, arduinoType);
}

void ppuck::init(int aledNum1, int aledNum2, int aledNum3, int aledNum4, String arduinoType) {
    _pinState = new pinduinoPins(arduinoType);

    if (arduinoType == "PPUC-1.0") {
        ALED1 = new AddressableStrip(aledNum1, 69, _pinState); // A15
        ALED2 = new AddressableStrip(aledNum2, 68, _pinState); // A14
        ALED3 = new AddressableStrip(aledNum3, 67, _pinState); // A13
        ALED4 = new AddressableStrip(aledNum4, 66, _pinState); // A12
        RGB1 = new RGBStrip(11, 12, 13); // pins 11,12,13
        RGB2 = new RGBStrip(8, 9, 10); // pins 8,9,10
        RGB3 = new RGBStrip(5, 6, 7); // pins 5,6,7
        DATAPORT1 = new DataPort(69);
        DATAPORT2 = new DataPort(68);
        DATAPORT3 = new DataPort(67);
        DATAPORT4 = new DataPort(66);
        _switchMatrix = new SwitchMatrix();
        _pin2Dmd = new PIN2DMD();
        _pupSerial = new PUPSerial();
    } else {
        Serial.print("Unsupported Arduino board: ");
        Serial.println(arduinoType);
    }
}

pinduinoPins *ppuck::pinState() {
    return _pinState;
}

SwitchMatrix *ppuck::switchMatrix() {
    return _switchMatrix;
}

PIN2DMD *ppuck::pin2Dmd() {
    return _pin2Dmd;
}

PUPSerial *ppuck::pupSerial() {
    return _pupSerial;
}

RGBStrip *ppuck::rgbLED1() {
    return RGB1;
}

RGBStrip *ppuck::rgbLED2() {
    return RGB2;
}

RGBStrip *ppuck::rgbLED3() {
    return RGB3;
}


RGBStrip *ppuck::rgbLED4() {
    return RGB4;
}

AddressableStrip *ppuck::adrLED1() {
    return ALED1;
}

AddressableStrip *ppuck::adrLED2() {
    return ALED2;
}

AddressableStrip *ppuck::adrLED3() {
    return ALED3;
}

AddressableStrip *ppuck::adrLED4() {
    return ALED4;
}

AddressableMatrix *ppuck::adrMatrix(AddressableStrip *adr, int col, int row, int start) {
    return new AddressableMatrix(adr, col, row, start);
}

DataPort *ppuck::port1() {
    return DATAPORT1;
}

DataPort *ppuck::port2() {
    return DATAPORT2;
}

DataPort *ppuck::port3() {
    return DATAPORT3;
}

DataPort *ppuck::port4() {
    return DATAPORT4;
}

//fade out all addressable strips
void ppuck::fadeOutAllAdr(float time) {
    time = time / 256;
    for (int i = 1; i < 255; i++) {
        _pinState->update();
        if (time) { delay(time); }
        ALED1->strip()->setBrightness(256 - i);
        ALED2->strip()->setBrightness(256 - i);
        ALED1->strip()->show();
        ALED2->strip()->show();
    }
    ALED1->clear();
    ALED1->strip()->setBrightness(255);
    ALED2->clear();
    ALED2->strip()->setBrightness(255);
}

//fade in all addressable strips
//note that strip colors must be previously set.  
//E.g.,:  ALED1->color("red", 1);  //brightness of 1

void ppuck::colorAllAdrRGB(int r, int g, int b) {
    ALED1->colorRGB(r, g, b);
    ALED2->colorRGB(r, g, b);
}

void ppuck::colorAllAdr(String color) {
    int r = 0;
    int g = 0;
    int b = 0;
    ALED1->color2RGB(color, r, g, b);
    colorAllAdrRGB(r, g, b);
}

void ppuck::fadeInAllAdrRGB(int r, int g, int b, float time) {
    time = time / 256;
    ALED1->strip()->setBrightness(1);
    ALED1->strip()->show();
    ALED2->strip()->setBrightness(1);
    ALED2->strip()->show();
    colorAllAdrRGB(r, g, b);
    for (int i = 2; i < 256; i++) {
        _pinState->update();
        if (time) { delay(time); }
        ALED1->strip()->setBrightness(i);
        ALED2->strip()->setBrightness(i);
        ALED1->strip()->show();
        ALED2->strip()->show();
    }
}

void ppuck::fadeInAllAdr(String color, float time) {
    int r = 0;
    int g = 0;
    int b = 0;
    ALED1->color2RGB(color, r, g, b);
    fadeInAllAdrRGB(r, g, b, time);
}

void ppuck::fadeAllAdrRGB2RGB(float r1, float g1, float b1, float r2, float g2, float b2, float time) {
    time = time / 256;
    ALED1->colorRGB(r1, g1, b1, 250);
    ALED2->colorRGB(r1, g1, b1, 250);
    //ALED3->colorRGB(r1, g1, b1, 250);
    ALED1->strip()->show();
    ALED2->strip()->show();
    //ALED3->strip()->show();
    if (time < 1) { time = 0; }
    float rcs = abs(r1 - r2) / 256;
    if (r2 > r1) { rcs = rcs * -1; }
    float gcs = abs(g1 - g2) / 256;
    if (g2 > g1) { gcs = gcs * -1; }
    float bcs = abs(b1 - b2) / 256;
    if (b2 > b1) { bcs = bcs * -1; }
    for (int i = 1; i < 256; i++) {
        _pinState->update();
        if (time) { delay(time); }
        float r = r1 - (rcs * i);
        float g = g1 - (gcs * i);
        float b = b1 - (bcs * i);
        ALED1->colorRGB(r, g, b, 250);
        ALED2->colorRGB(r, g, b, 250);
        //ALED3->colorRGB(r, g, b, 250);
        ALED1->strip()->show();
        ALED2->strip()->show();
        //ALED3->strip()->show();
    }
}

void ppuck::fadeAllAdrColor2Color(String color1, String color2, float time) {
    int r1, g1, b1;
    int r2, g2, b2;
    ALED1->color2RGB(color1, r1, g1, b1);
    ALED1->color2RGB(color2, r2, g2, b2);
    fadeAllAdrRGB2RGB(r1, g1, b1, r2, g2, b2, time);
}

void ppuck::chaseAllAdr2RGB(float r1, float g1, float b1, float r2, float g2, float b2, float span, int time, int dir) {
    int pos;
    int numP = ALED1->strip()->numPixels();
    if (ALED2->strip()->numPixels() > numP) { numP = ALED2->strip()->numPixels(); }
    //if (ALED3->strip()->numPixels() > numP) {numP = ALED3->strip()->numPixels();}
    if (dir > 0) { pos = numP + span; }
    else { pos = 0 - span; }
    float rcs = abs(r1 - r2) / (numP);
    if (r2 > r1) { rcs = rcs * -1; }
    float gcs = abs(g1 - g2) / (numP);
    if (g2 > g1) { gcs = gcs * -1; }
    float bcs = abs(b1 - b2) / (numP);
    if (b2 > b1) { bcs = bcs * -1; }

    for (int i = 0; i < numP + 2 * span + 1; i++) {
        _pinState->update();
        float r = r1;
        float g = g1;
        float b = b1;
        if (i > span) {
            r = r1 - (rcs * (i - span));
            g = g1 - (gcs * (i - span));
            b = b1 - (bcs * (i - span));
        }
        for (int j = -span; j <= span; j++) {
            { ALED1->strip()->setPixelColor(pos + j, 0, 0, 0); }
            { ALED2->strip()->setPixelColor(pos + j, 0, 0, 0); }
            //if (pos < ALED3->strip()->numPixels()+span) {ALED3->strip()->setPixelColor(pos+j, 0,0,0);}
        }
        { ALED1->RGBBand(pos, r, g, b, span); }
        { ALED2->RGBBand(pos, r, g, b, span); }
        //if (pos < ALED3->strip()->numPixels()+span+1) {ALED3->RGBBand(pos, r, g, b, span);}
        if (time) { delay(time); }
        if (dir > 0) { pos--; }
        else { pos++; }
    }
}

void ppuck::chaseAllAdr2Color(String color1, String color2, float span, int time, int dir) {
    int r1, g1, b1;
    int r2, g2, b2;
    ALED1->color2RGB(color1, r1, g1, b1);
    ALED2->color2RGB(color2, r2, g2, b2);
    chaseAllAdr2RGB(r1, g1, b1, r2, g2, b2, span, time, dir);
}

void ppuck::chaseAllAdr2RGBFromPoint(int pos, float r1, float g1, float b1, float r2, float g2, float b2, int span,
                                        int time) {
    int numP = ALED1->strip()->numPixels();
    if (ALED2->strip()->numPixels() > numP) { numP = ALED2->strip()->numPixels(); }
    //if (ALED3->strip()->numPixels() > numP) {numP = ALED3->strip()->numPixels();}
    int max_pos = pos;  //max distance to edge of strip from position pos
    if (max_pos < numP - pos) { max_pos = numP - pos; }
    //color step size
    float rcs = abs(r1 - r2) / (max_pos);
    if (r2 > r1) { rcs = rcs * -1; }
    float gcs = abs(g1 - g2) / (max_pos);
    if (g2 > g1) { gcs = gcs * -1; }
    float bcs = abs(b1 - b2) / (max_pos);
    if (b2 > b1) { bcs = bcs * -1; }

    for (int i = 0; i < max_pos + span; i++) {
        _pinState->update();

        // Rather than being sneaky and erasing just the tail pixel,
        // it's easier to erase it all and draw a new one next time.
        for (int j = -span; j <= span; j++) {
            if (ALED1->strip()->numPixels() > 0 && pos < ALED1->strip()->numPixels() + span) {
                ALED1->strip()->setPixelColor(pos - i + j, 0, 0, 0);
                ALED1->strip()->setPixelColor(pos + i + j, 0, 0, 0);
            }
            if (ALED2->strip()->numPixels() > 0 && pos < ALED2->strip()->numPixels() + span) {
                ALED2->strip()->setPixelColor(pos - i + j, 0, 0, 0);
                ALED2->strip()->setPixelColor(pos + i + j, 0, 0, 0);
            }
            //if (ALED3->strip()->numPixels() > 0 && pos < ALED3->strip()->numPixels()+span) {ALED3->strip()->setPixelColor(pos-i+j, 0,0,0); ALED3->strip()->setPixelColor(pos+i+j, 0,0,0);}
        }

        float r = r1;
        float g = g1;
        float b = b1;
        r = r1 - (rcs * (i));
        g = g1 - (gcs * (i));
        b = b1 - (bcs * (i));
        if (ALED1->strip()->numPixels() > 0) {
            ALED1->RGBBand(pos - i, r, g, b, span);
            ALED1->RGBBand(pos + i, r, g, b, span);
        }
        if (ALED2->strip()->numPixels() > 0) {
            ALED2->RGBBand(pos - i, r, g, b, span);
            ALED2->RGBBand(pos + i, r, g, b, span);
        }
        //if ( (ALED3->strip()->numPixels() > 0) && (pos+i < ALED3->strip()->numPixels()+span+1) ) {ALED3->RGBBand(pos-i, r, g, b, span); ALED2->RGBBand(pos+i, r, g, b, span);}
        if (time) { delay(time); }
    }
    for (int i = 0; i < span; i++) {
        _pinState->update();
    }
}

void ppuck::testRGBStrip(RGBStrip *strip) {
    strip->set("red");
    delay(300);
    strip->set("green");
    delay(300);
    strip->set("blue");
    delay(300);
    strip->set("yellow");
    delay(300);
    strip->set("purple");
    delay(300);
    strip->set("cyan");
    delay(300);
    strip->set("white");
    delay(300);
    strip->fadeIn("red", 300);
    delay(100);
    strip->fadeOut(300);
    delay(500);
    strip->fadeIn("green", 300);
    delay(100);
    strip->fadeOut(300);
    delay(500);
    strip->fadeIn("blue", 300);
    delay(100);
    strip->fadeOut(300);
    delay(500);
    strip->fadeIn("yellow", 300);
    delay(100);
    strip->fadeOut(300);
    delay(500);
    strip->fadeIn("purple", 300);
    delay(100);
    strip->fadeOut(300);
    delay(500);
    strip->fadeIn("cyan", 300);
    delay(100);
    strip->fadeOut(300);
    delay(500);
    strip->fadeIn("white", 300);
    delay(100);
    strip->fadeOut(300);
    delay(500);
}

void ppuck::testRGBStrip1() {
    testRGBStrip(RGB1);
}

void ppuck::testRGBStrip2() {
    testRGBStrip(RGB2);
}

void ppuck::testRGBStrip3() {
    testRGBStrip(RGB3);
}

void ppuck::testRGBStrip4() {
    testRGBStrip(RGB4);
}


void ppuck::testSpeakerAdrLED(AddressableStrip *strip) {
    //chase2RGBCont(float r1, float g1, float b1, float r2, float g2, float b2, float span, int time, int dir, int startLED, int endLED)

    // Slow Red/Blue
    strip->chase2RGBCont(255, 0, 0, 0, 0, 255, 6, 100, -1, 0, 23);
    strip->chase2RGBCont(0, 0, 255, 255, 0, 0, 6, 100, -1, 0, 23);

    strip->chase2RGBCont(255, 0, 0, 0, 0, 255, 6, 100, 1, 0, 23);
    strip->chase2RGBCont(0, 0, 255, 255, 0, 0, 6, 100, 1, 0, 23);

    // Fast Red/Blue
    strip->chase2RGBCont(255, 0, 0, 0, 0, 255, 6, 10, -1, 0, 23);
    strip->chase2RGBCont(0, 0, 255, 255, 0, 0, 6, 10, -1, 0, 23);

    strip->chase2RGBCont(255, 0, 0, 0, 0, 255, 6, 10, 1, 0, 23);
    strip->chase2RGBCont(0, 0, 255, 255, 0, 0, 6, 10, 1, 0, 23);

    // Fast cylon Red
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, 1, 0, 23);

    //Speed Up!
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 100, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 80, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 60, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 40, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, 1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 10, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 20, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 40, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 60, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 80, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 100, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 0, 0, 1, 100, -1, 0, 23);
    strip->chase2RGBCont(255, 0, 0, 255, 255, 255, 1, 10, -1, 0, 23);
    strip->chase2RGBCont(255, 255, 255, 10, 10, 10, 1, 10, -1, 0, 23);


}

void ppuck::testSpeakerAdrLED1() {
    testSpeakerAdrLED(ALED1);

}


void ppuck::testAdrLED(AddressableStrip *strip) {
    strip->chase("green", 10, 10, 1);
    strip->chase("blue", 10, 10, -1);
    strip->chase("red", 10, 10, 1);
    strip->chase("white", 10, 10, -1);
    strip->chase2Color("red", "green", 10, 10, 1);
    strip->chase2Color("green", "blue", 10, 10, -1);
    strip->chase2Color("blue", "red", 10, 10, 1);
    strip->chase2Color("red", "white", 10, 10, -1);
    strip->spreadInFromPoint(strip->strip()->numPixels() / 2, "red", 1000);
    strip->fadeOut(500);
    strip->spreadInFromPoint(strip->strip()->numPixels() / 2, "green", 1000);
    strip->fadeOut(500);
    strip->spreadInFromPoint(strip->strip()->numPixels() / 2, "blue", 1000);
    strip->fadeOut(500);
    strip->spreadInFromPoint(strip->strip()->numPixels() / 2, "white", 1000);
    strip->fadeOut(500);
    strip->spreadInFromPoint2Color(strip->strip()->numPixels() / 2, "red", "green", 1000);
    strip->fadeOut(500);
    strip->spreadInFromPoint2Color(strip->strip()->numPixels() / 2, "green", "blue", 1000);
    strip->fadeOut(500);
    strip->spreadInFromPoint2Color(strip->strip()->numPixels() / 2, "blue", "red", 1000);
    strip->fadeOut(500);
    strip->spreadInFromPoint2Color(strip->strip()->numPixels() / 2, "blue", "white", 1000);
    strip->fadeOut(500);
    strip->spreadInFromPoint2Color(strip->strip()->numPixels() / 2, "white", "red", 1000);
    strip->fadeOut(500);
    strip->spreadInFromPoint2Color(strip->strip()->numPixels() / 2, "white", "green", 1000);
    strip->fadeOut(500);
    strip->spreadInFromPoint(strip->strip()->numPixels() / 2, "red", 1000);
    strip->spreadOutFromPoint(strip->strip()->numPixels() / 2, 1000);
    strip->spreadInFromPoint(strip->strip()->numPixels() / 2, "green", 1000);
    strip->spreadOutToPoint(strip->strip()->numPixels() / 2, 1000);
    strip->spreadInFromPoint(strip->strip()->numPixels() / 2, "blue", 1000);
    strip->spreadOutToPoint(strip->strip()->numPixels() / 2, 1000);
    strip->spreadInFromPoint(strip->strip()->numPixels() / 2, "white", 1000);
    strip->spreadOutToPoint(strip->strip()->numPixels() / 2, 1000);
    strip->bullet2Color("red", "green", 20, 5, 1);
    strip->bullet2Color("green", "blue", 20, 5, -1);
    strip->bullet2Color("blue", "red", 20, 5, 1);
    for (int i = 0; i < 20; i = i + 1) {
        strip->explosion(random(strip->getNumLEDs()), "red", random(20) + 5);
    }
    strip->rainbow(10);
    strip->rainbow(10);
    strip->rainbow(10);
    strip->rainbow(10);
    strip->fadeOut(1000);
    delay(500);

    strip->color("red", 255);
    delay(200);
    strip->color("green", 255);
    delay(200);
    strip->color("blue", 255);
    delay(200);
    strip->color("yellow", 255);
    delay(200);
    strip->color("cyan", 255);
    delay(200);
    strip->color("purple", 255);
    delay(200);
    strip->color("white", 255);
    delay(200);
    strip->color("orange", 255);
    delay(200);
    strip->color("lime", 255);
    delay(200);
    strip->color("sky", 255);
    delay(200);
    strip->color("mint", 255);
    delay(200);
    strip->color("magenta", 255);
    delay(200);
    strip->color("lavender", 255);
    delay(200);
    strip->fadeOut(100);
    delay(200);
    strip->fadeIn("Red", 200);
    strip->fadeOut(200);
    strip->fadeIn("blue", 200);
    strip->fadeOut(200);
    strip->fadeIn("green", 200);
    strip->fadeOut(200);
    delay(200);
}

void ppuck::testAdrLEDAlpha(AddressableStrip *strip) {
    strip->bullet("red", 10, 1, 1);
    strip->bullet("red", 10, 1, -1);
    strip->bullet("blue", 10, 1, 1);
    strip->bullet("blue", 10, 1, -1);
    strip->bullet2Color("red", "blue", 10, 1, 1);
    strip->bullet2Color("blue", "red", 10, 1, -1);
    strip->bullet2Color("blue", "white", 10, 1, 1);
    strip->bullet2Color("white", "blue", 10, 1, -1);
    strip->bullet2Color("red", "white", 10, 1, 1);
    strip->bullet2Color("white", "red", 10, 1, -1);
    strip->bullet2Color("orange", "red", 10, 1, 1);
    strip->bullet2Color("red", "orange", 10, 1, -1);
    strip->bullet2Color("white", "blue", 10, 1, 1);
    strip->bullet2Color("blue", "white", 10, 1, -1);

}

void ppuck::testAdrLED1() {
    testAdrLED(ALED1);
}

void ppuck::testAdrLED2() {
    testAdrLED(ALED2);
}

void ppuck::testAdrLED3() {
    testAdrLED(ALED3);
}

void ppuck::testAdrLED4() {
    testAdrLED(ALED4);
}

void ppuck::testAdrLED1Alpha() {
    testAdrLEDAlpha(ALED1);
}

void ppuck::testAdrLED2Alpha() {
    testAdrLEDAlpha(ALED2);
}

void ppuck::testAdrLED3Alpha() {
    testAdrLEDAlpha(ALED3);
}

void ppuck::testAdrLED4Alpha() {
    testAdrLEDAlpha(ALED4);
}