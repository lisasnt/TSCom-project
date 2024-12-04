#include "BLE.h"

BL::BL(){

}

void BL::begin() {
    while(!BLE.begin()){}
    BLE.setLocalName("Board_g26");
    BLE.setAdvertisedService(Group40Service);
    Group40Service.addCharacteristic(distanceCharacteristic);
    BLE.addService(Group40Service);
    BLE.advertise();
}

void BL::writeValue(uint32_t val) {
    BLE.poll();

    // if a central is connected to the peripheral:
    if (BLE.connected()) {
    static unsigned long lastUpdate = 0;
    static int32_t value = 0;
    unsigned long currentMillis = millis();
        if (currentMillis - lastUpdate >= 100) { 
            lastUpdate = currentMillis;
            distanceCharacteristic.writeValue((int32_t)val);
        }
    }
}

uint32_t BL::readValue() {
    if (BLE.connected()) {
        if (distanceCharacteristic.written()) {
            return distanceCharacteristic.value();
        }
    }
    return 0;
}