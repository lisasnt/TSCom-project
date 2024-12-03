#if !( ARDUINO_ARCH_NRF52840 && TARGET_NAME == ARDUINO_NANO33BLE )
    #error This code is designed to run on nRF52-based Nano-33-BLE boards using mbed-RTOS platform! Please check your Tools->Board setting.
#endif

#define TIMER_INTERRUPT_DEBUG        0
#define _TIMERINTERRUPT_LOGLEVEL_    0

#include "UltrasonicSensor.h"
#include "IMUSensor.h"
#include "BLE.h"

#define ULTR_TRIG_PIN 8
#define ULTR_ECHO_PIN 10

UltrasonicSensor ultrasonicSensor(ULTR_TRIG_PIN, ULTR_ECHO_PIN);
BL ble = BL();

void setup() {
    Serial.begin(9600);
    ultrasonicSensor.begin();
    IMU.init();
    ble.begin();
}

void loop() {
    float ultr_distance = ultrasonicSensor.getDistance();
    Serial.println("Ultrasonic sensor distance: " + String(ultr_distance) + " cm");

    float IMU_tilt = IMU.getTilt();
    //Serial.println("IMU sensor tilit " + String(IMU_tilt) + "degrees");
  
    ble.writeValue(ultr_distance);
    //Serial.println("BLE read: " + String(ble.readValue()));

    delay(1000);
}