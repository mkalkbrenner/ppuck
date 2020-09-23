// These defines must be placed at the beginning before #include "TimerInterrupt.h"
#define TIMER_INTERRUPT_DEBUG      0
#define USE_TIMER_1 false
#define USE_TIMER_2 false
#define USE_TIMER_3 false
// Switch Matrix
#define USE_TIMER_4 true
// Non blocking effects
#define USE_TIMER_5 true

#include "TimerInterrupt.h"

#include "src/SwitchMatrix.h"

volatile unsigned int strobeReadOffset = 0;
volatile unsigned long col1Strobe = 0L;
volatile unsigned int col8Strobe = 0;

SwitchMatrix switchMatrix(8, 3);

void strobeDetectionColumn1() {
    // @see https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
    // micros() works initially but will start behaving erratically after 1-2 ms.
    // So this call right at the beginning of the interrupt should be fine.
    col1Strobe = micros();
}

void strobeDetectionColumn8() {
    // @see https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
    // micros() works initially but will start behaving erratically after 1-2 ms.
    // So this call right at the beginning of the interrupt should be fine.
    col8Strobe = micros() - col1Strobe;
}

void readSwitches() {
    switchMatrix.readSwitches();
}

void strobeColumn1() {
    delayMicroseconds(strobeReadOffset);
    ITimer4.restartTimer();
    readSwitches();
}

void strobeColumn8() {
    ITimer4.stopTimer();
}

void setup() {
    DDRA = 0; // all PORTA is input
    Serial.begin(9600);
    Serial.print("Wait for pinball machine booting ...");
    // wait for pinball machine finishing boot process
    delay(5000);

    Serial.print("Start switch matrix strobe detection ...");
    attachInterrupt(digitalPinToInterrupt(3), strobeDetectionColumn8, RISING);
    attachInterrupt(digitalPinToInterrupt(2), strobeDetectionColumn1, FALLING);

    unsigned long strobesDurationSum = 0L;
    for (int i = 0; i < 200; i++) {
        strobesDurationSum = strobesDurationSum + col8Strobe;
        delay(20);
    }
    unsigned int strobesTotalDuration = strobesDurationSum / 200;
    Serial.print("Strobes total duration (micro seconds): ");
    Serial.println(strobesTotalDuration);

    attachInterrupt(digitalPinToInterrupt(3), strobeDetectionColumn8, FALLING);
    attachInterrupt(digitalPinToInterrupt(2), strobeDetectionColumn1, RISING);
    strobesDurationSum = 0L;
    for (int i = 0; i < 200; i++) {
        strobesDurationSum = strobesDurationSum + col8Strobe;
        delay(20);
    }
    detachInterrupt(digitalPinToInterrupt(2));
    detachInterrupt(digitalPinToInterrupt(3));
    unsigned int strobeDuration = (strobesTotalDuration - (strobesDurationSum / 200)) / 2;
    Serial.print("Strobe duration (micro seconds): ");
    Serial.println(strobeDuration);
    unsigned int strobesGap = (strobesTotalDuration - (strobeDuration * 8)) / 7;
    Serial.print("Strobes gap (micro seconds): ");
    Serial.println(strobesGap);
    // f = 1 / s = 1000000 / us
    float strobeFrequency = 1000000.0f / (strobeDuration + strobesGap);
    Serial.print("Strobe frequency (hertz): ");
    Serial.println(strobeFrequency);
    strobeReadOffset = strobeDuration / 2;
    Serial.print("Strobe read offset (micro seconds): ");
    Serial.println(strobeReadOffset);

    ITimer4.init();
    ITimer4.attachInterrupt(strobeFrequency, readSwitches, 0L);
    ITimer4.stopTimer();

    attachInterrupt(digitalPinToInterrupt(2), strobeColumn1, FALLING);
    attachInterrupt(digitalPinToInterrupt(3), strobeColumn8, RISING);
}

void loop() {
    switchMatrix.dump();
}
