#include "InfraRedSensor.h"

InfraRedSensor* InfraRedSensor::instance = nullptr;

InfraRedSensor::InfraRedSensor(uint8_t analogPin)
    : _analogPin(analogPin) {
    instance = this;
}

uint32_t InfraRedSensor::getADCValue() {
    return analogRead(_analogPin);
}

float InfraRedSensor::getDistanceWhite(uint32_t analogValue){
    float val = (float)analogValue;
    return (1.55058830e-02 * val 
           -1.07071156e-05 * val * val
           + 6.27489604e-01 * ((1 / (val) )* 1000) * ((1 / (val) )* 1000)
           -5.377095188616198) * CM_TO_MMe_1;
}

float InfraRedSensor::getDistanceBlue(uint32_t analogValue){
    float val = (float)analogValue;
    return (9.59252396e-03 * val 
           -7.26802138e-06 * val * val 
           + 4.38981050e-01 * ((1 / (val) )* 1000) *  ((1 / (val) )* 1000)
           -2.472508082644848) * CM_TO_MMe_1;
}

float InfraRedSensor::getDistanceRed(uint32_t analogValue){
    float val = (float)analogValue;
    return (1.70508284e-02 * val 
           -1.21191332e-05 * val * val
           + 4.64108649e-01 * ((1 / (val) )* 1000) *  ((1 / (val) )* 1000)
           -5.502090525116139) * CM_TO_MMe_1;
}
















