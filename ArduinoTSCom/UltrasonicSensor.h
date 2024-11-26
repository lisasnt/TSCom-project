#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "TimerInterrupt_Generic.h"

#define MICROS_TO_CM            58.0
// Timers' Interval in microsecs
#define TIMER_INTERVAL_50mS     50000    
#define TIMER_INTERVAL_10uS     10

class UltrasonicSensor {
public:
    UltrasonicSensor(uint8_t trigPin, uint8_t echoPin);
    void begin();
    float getDistance();
    static void staticTimerHandler0();
    static void staticTimerHandler1();
    static void staticEchoHandler();

private:
    uint8_t _trigPin;
    uint8_t _echoPin;
    static volatile bool _isEchoOn;
    static volatile uint32_t _startTime;
    static volatile uint32_t _endTime;
    static volatile bool _isFirstToggleDone;
    static volatile bool _toggle0;
    static UltrasonicSensor* instance;
    
    void timerHandler0();
    void timerHandler1();
    void echoHandler();

    NRF52_MBED_Timer _timer0;
    NRF52_MBED_Timer _timer1;
};

#endif