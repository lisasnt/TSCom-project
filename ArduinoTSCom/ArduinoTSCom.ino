#if !( ARDUINO_ARCH_NRF52840 && TARGET_NAME == ARDUINO_NANO33BLE )
    #error This code is designed to run on nRF52-based Nano-33-BLE boards using mbed-RTOS platform! Please check your Tools->Board setting.
#endif

#define TIMER_INTERRUPT_DEBUG        0
#define _TIMERINTERRUPT_LOGLEVEL_    0

#include "UltrasonicSensor.h"
#include "IMUSensor.h"
#include "SensorFusion.h"
#include "BLE.h"

#define ULTR_TRIG_PIN 8
#define ULTR_ECHO_PIN 10

UltrasonicSensor ultrasonicSensor(ULTR_TRIG_PIN, ULTR_ECHO_PIN);
BL ble = BL();

void setup() {
    Serial.begin(9600);
    ultrasonicSensor.begin();
    IMU.init();
    ble.begin();
}

void loop() {

    /*
        Many of the functions bellow return floats, should be changed to uintX_t where pssoible. 
    */

    unit32_t d_ultra = 0;
    uint32_t v_infra = 0;
    uint32_t tilt_angle = 0;
    for(i = 1; i <= 5, i++){
        //Preforms measurments and incremented average formula
        d_ultra += (ultrasonicSensor.getDistance()-d_ultra)/i;
        v_infra += (analogRead(A7)-v_infra)/i;
        tilt_angle += (IMU.getTilt()-tilt_angle)/i;
    }

    Serial.println("Ultrasonic sensor distance: " + String(d_ultra) + " cm");
    Serial.println("Infrared sensor measurment: " + String(v_infra) + " ?");
    Serial.println("Tilit angle: " + String(tilt_Angle) + "degrees");

    float d_ultra_comp = tiltComp(d_ultra, tilt_Angle);
    Serial.println("Angle compensated ultrasonic distance: " + String(d_ultra_comp) + " cm");

    //float d_infra = infraToDistance(v_infra, infra_treshold, d_ultra_comp, ultra_treshold);
    //Serial.println("Infrared sensor distance: " + String(d_infra) + " cm");

    //float d_infra_comp = tilitComp(d_infra, tilt_Angle);
    //Serial.println("Angle compensated infrared distance: " + String(d_infra_comp) + " cm");

    //float d_comb = SensorFusion(d_ultra_comb, d_infra_comb);
    //Serial.println("Sensor fused distance: " + String(d_comb) + " cm");
  
    ble.writeValue(ultr_distance);
    float other_group_distance = ble.readValue(); 
    if (other_group_distance != -1) {
        Serial.println("BLE read: " + String(other_group_distance));
    }

    delay(1000);
ti}