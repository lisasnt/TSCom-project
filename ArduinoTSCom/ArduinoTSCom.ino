#if !( ARDUINO_ARCH_NRF52840 && TARGET_NAME == ARDUINO_NANO33BLE )
    #error This code is designed to run on nRF52-based Nano-33-BLE boards using mbed-RTOS platform! Please check your Tools->Board setting.
#endif

#define TIMER_INTERRUPT_DEBUG        0
#define _TIMERINTERRUPT_LOGLEVEL_    0

#include "UltrasonicSensor.h"
#include "IMUSensor.h"
#include "SensorFusion.h"
#include "BLE.h"
#include "InfraRedSensor.h"

#define ULTR_TRIG_PIN 8
#define ULTR_ECHO_PIN 10
#define IR_SENSOR     A7 

#define N_SAMPLES   4

#define WHITE_WALL
//#define BLUE_WALL
//#define RED_WALL

UltrasonicSensor ultrasonicSensor(ULTR_TRIG_PIN, ULTR_ECHO_PIN);
BL ble = BL();
InfraRedSensor irSensor(IR_SENSOR);

uint8_t cnt = N_SAMPLES;

void setup() {
    Serial.begin(9600);
    ultrasonicSensor.begin();
    IMU.init();
    ble.begin();
}

void loop() {
    float sum_ir_distaces, sum_tilt_angles;
    
    uint32_t avg_ultr_distance = ultrasonicSensor.getAvarageDistance();
    while(cnt) {
        #ifdef WHITE_WALL
        sum_ir_distaces += irSensor.getDistanceWhite(irSensor.getADCValue());
        #endif
        #ifdef BLUE_WALL
        sum_ir_distaces += irSensor.getDistanceBlue(irSensor.getADCValue());
        #endif
        #ifdef RED_WALL
        sum_ir_distaces += irSensor.getDistanceRed(irSensor.getADCValue());
        #endif
        sum_tilt_angles += IMU.getTilt();
        cnt--;
    }
    cnt = N_SAMPLES;

    float avg_ir_distance = sum_ir_distaces / N_SAMPLES;    
    float tilt_angle = sum_tilt_angles / N_SAMPLES;

    //float final_value = sensorFusion(tiltComp(avg_ultr_distance, tilt_angle), tiltComp(avg_ir_distance, tilt_angle));
    float final_value = sensorFusion(avg_ultr_distance, avg_ir_distance);

    //Serial.println("Ultrasonic sensor avg distance: " + String(avg_ultr_distance) + " mm*e-1");
    //Serial.println("Infrared sensor measurment: " + String(avg_ir_distance) + " mm*e-1");
    //Serial.println("Tilt angle = " + String(IMU.getTilt()) + " °");
    Serial.println("Estimated distance = " + String(final_value) + " mm*e-1");

   
    // BLE implementation
    ble.writeValue((uint32_t)final_value);
    float other_group_distance = ble.readValue(); 
    if (other_group_distance != 0) {
        Serial.println("BLE read: " + String(other_group_distance));
    }
    delay(1000);
}