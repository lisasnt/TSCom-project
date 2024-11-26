#if !( ARDUINO_ARCH_NRF52840 && TARGET_NAME == ARDUINO_NANO33BLE )
    #error This code is designed to run on nRF52-based Nano-33-BLE boards using mbed-RTOS platform! Please check your Tools->Board setting.
#endif

#define TIMER_INTERRUPT_DEBUG        0
#define _TIMERINTERRUPT_LOGLEVEL_    0

#include "UltrasonicSensor.h"

#define ULTR_TRIG_PIN 8
#define ULTR_ECHO_PIN 10

UltrasonicSensor ultrasonicSensor(ULTR_TRIG_PIN, ULTR_ECHO_PIN);

void setup() {
    Serial.begin(9600);
    ultrasonicSensor.begin();
}

void loop() {
    float ultr_distance = ultrasonicSensor.getDistance();
    Serial.println("Ultrasonic sensor distance: " + String(ultr_distance) + " cm");
    delay(100);
}