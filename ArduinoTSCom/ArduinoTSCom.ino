#if !( ARDUINO_ARCH_NRF52840 && TARGET_NAME == ARDUINO_NANO33BLE )
    #error This code is designed to run on nRF52-based Nano-33-BLE boards using mbed-RTOS platform! Please check your Tools->Board setting.
#endif

#define TIMER_INTERRUPT_DEBUG        0
#define _TIMERINTERRUPT_LOGLEVEL_    0

#include "UltrasonicSensor.h"
#include "IMUSensor.h"
#include "SensorFusion.h"

#define ULTR_TRIG_PIN 8
#define ULTR_ECHO_PIN 10

UltrasonicSensor ultrasonicSensor(ULTR_TRIG_PIN, ULTR_ECHO_PIN);

void setup() {
    Serial.begin(9600);
    ultrasonicSensor.begin();
    IMU.init();

}

void loop() {
    float d_ultra = ultrasonicSensor.getDistance();
    Serial.println("Ultrasonic sensor distance: " + String(d_ultra) + " cm");

    float IMU_tilt = IMU.getTilt();
    Serial.println("Tilit angle: " + String(IMU_tilt) + "degrees");

    float d_ultra_comp = tiltComp(d_ultra, IMU_tilt);
    Serial.println("Angle compensated ultrasonic distance: " + String(d_ultra_comp) + " cm");

    delay(1000);
ti}