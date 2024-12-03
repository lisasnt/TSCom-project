#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

class InfraRedSensor {
public:
    InfraRedSensor(uint8_t _analogPin);
    float getADCValue();

private:
    uint8_t _analogPin;
    static InfraRedSensor* instance;
};

#endif