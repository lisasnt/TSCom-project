#include "InfraRedSensor.h"

InfraRedSensor* InfraRedSensor::instance = nullptr;

InfraRedSensor::InfraRedSensor(uint8_t analogPin)
    : _analogPin(analogPin) {
    instance = this;
}

float InfraRedSensor::getADCValue() {
    return analogRead(_analogPin);
}
