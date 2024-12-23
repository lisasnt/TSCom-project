#ifndef BLE_H
#define BLE_H

#include <ArduinoBLE.h>

#define UUID "082b91ae-e83c-11e8-9f32-f2801f1b9fd1"

BLEService Group40Service(UUID);
BLEIntCharacteristic distanceCharacteristic(UUID, BLERead | BLEWrite);

class BL{
public:
    BL();
    void begin();
    void writeValue(uint32_t);
    uint32_t readValue();
};

#endif