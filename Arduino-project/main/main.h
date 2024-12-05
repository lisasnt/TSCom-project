#if !( ARDUINO_ARCH_NRF52840 && TARGET_NAME == ARDUINO_NANO33BLE )
    #error This code is designed to run on nRF52-based Nano-33-BLE boards using mbed-RTOS platform! Please check your Tools->Board setting.
#endif

#define TIMER_INTERRUPT_DEBUG        0
#define _TIMERINTERRUPT_LOGLEVEL_    0

#include "UltrasonicSensor.h"
#include "IMUSensor.h"
#include "BLE.h"
#include "InfraRedSensor.h"

#define ULTR_TRIG_PIN   8
#define ULTR_ECHO_PIN   10
#define IR_SENSOR       A7 

#define N_SAMPLES   4

// Empirical Thresholds
#define IR_SENSOR_THRESHOLD     7.5
#define ULTR_SENSOR_THRESHOLD   14.5

#define DEG_TO_RAD  0.0174533 

/*
*    Sensor Fusion functions  
*/
float sensorFusion(float ultr_measurement, float ir_measurement);
float tiltCompensation(float distance, float angle);