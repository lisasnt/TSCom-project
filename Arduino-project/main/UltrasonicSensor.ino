#include "UltrasonicSensor.h"

volatile bool UltrasonicSensor::_isEchoOn = false;
volatile uint32_t UltrasonicSensor::_startTime = 0;
volatile uint32_t UltrasonicSensor::_endTime = 0;
volatile uint32_t UltrasonicSensor::_samples[DIM_SAMPLES] = {0,0,0,0};
volatile uint8_t  UltrasonicSensor::_sampleIndex = 0;
volatile bool UltrasonicSensor::_isFirstToggleDone = false;
volatile bool UltrasonicSensor::_toggle0 = true;
UltrasonicSensor* UltrasonicSensor::instance = nullptr;

UltrasonicSensor::UltrasonicSensor(uint8_t trigPin, uint8_t echoPin) 
    : _trigPin(trigPin), _echoPin(echoPin), _timer0(NRF_TIMER_3), _timer1(NRF_TIMER_4) {
    instance = this;
}

void UltrasonicSensor::begin() {
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
    digitalWrite(_trigPin, LOW);
    attachInterrupt(digitalPinToInterrupt(_echoPin), staticEchoHandler, CHANGE);
    _timer1.attachInterruptInterval(TIMER_INTERVAL_50mS, staticTimerHandler1);
}

void UltrasonicSensor::staticTimerHandler0() {
    if (instance) instance->timerHandler0();
}

void UltrasonicSensor::staticTimerHandler1() {
    if (instance) instance->timerHandler1();
}

void UltrasonicSensor::staticEchoHandler() {
    if (instance) instance->echoHandler();
}

void UltrasonicSensor::timerHandler0() {
    if (_isFirstToggleDone && _toggle0) {
        _timer0.stopTimer();
        _timer0.disableTimer();
        _isFirstToggleDone = false;
    }
    digitalWrite(_trigPin, _toggle0);
    _toggle0 = !_toggle0;
    _isFirstToggleDone = true;
}

void UltrasonicSensor::timerHandler1() {
    _timer0.attachInterruptInterval(TIMER_INTERVAL_10uS, staticTimerHandler0);
}

void UltrasonicSensor::echoHandler() {
    if (digitalRead(_echoPin) == HIGH) {
        _startTime = micros();
        _isEchoOn = true;
    } else if (_isEchoOn) {
        _endTime = micros();
        _isEchoOn = false; 
        _samples[_sampleIndex++] = _endTime - _startTime;
        if(_sampleIndex == DIM_SAMPLES) { 
            _sampleIndex = 0;
        }
    }
}

uint32_t UltrasonicSensor::getDistance() {
    static uint32_t distance;
    if (!_isEchoOn && _startTime != 0 && _endTime != 0) {
        if (_endTime >= _startTime) {
            distance = (_endTime - _startTime) / MICROS_TO_CM * CM_TO_MMe_1;
        } else { //deal overflow of micros()
            distance = (4294967295UL - _startTime + _endTime) / MICROS_TO_CM * CM_TO_MMe_1; 
        }
        _startTime = 0;
        _endTime = 0;
    }
    return distance;    
}

uint32_t UltrasonicSensor::getAvarageDistance() {
    static uint32_t distance;
        uint32_t avarage = 0;
            for (uint8_t i = 0; i < DIM_SAMPLES; i++) {
                avarage += _samples[i];
            }
            distance = (avarage / DIM_SAMPLES) / MICROS_TO_CM * CM_TO_MMe_1;
        _startTime = 0;
        _endTime = 0;
    //}
    return distance;    
}