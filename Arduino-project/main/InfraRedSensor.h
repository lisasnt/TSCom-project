#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

#define CM_TO_MMe_1     100

class InfraRedSensor {
public:
    InfraRedSensor(uint8_t _analogPin);
    uint32_t getADCValue();
    float getDistanceWhite(uint32_t v_infra);
    float getDistanceBlue(uint32_t v_infra);
    float getDistanceRed(uint32_t v_infra);

private:
    uint8_t _analogPin;
    static InfraRedSensor* instance;
};

#endif