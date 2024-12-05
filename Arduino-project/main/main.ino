#include "main.h"

/*
* Configuration section: Select the wall color for IR sensor calibration
* Uncomment ONE of the following defines based on the wall color being detected
*/
#define WHITE_WALL      // For white wall detection
//#define BLUE_WALL     // For blue wall detection
//#define RED_WALL      // For red wall detection

UltrasonicSensor ultrasonicSensor(ULTR_TRIG_PIN, ULTR_ECHO_PIN);
BL ble = BL();
InfraRedSensor irSensor(IR_SENSOR);

// Number of samples to average for more stable readings
uint8_t cnt = N_SAMPLES;

void setup() {
    Serial.begin(9600);
    ultrasonicSensor.begin();
    IMU.init();
    ble.begin();
}

void loop() {
    float sum_ir_distaces = 0; 
    //float sum_tilt_angles = 0; /* imu avarage does not work! */
    float avg_ultr_distance = ultrasonicSensor.getAvarageDistance();
    while(cnt) {
        #ifdef WHITE_WALL
        sum_ir_distaces += irSensor.getDistanceWhite(irSensor.getADCValue());
        #endif
        #ifdef BLUE_WALL
        sum_ir_distaces += irSensor.getDistanceBlue(irSensor.getADCValue());
        #endif
        #ifdef RED_WALL
        sum_ir_distaces += irSensor.getDistanceRed(irSensor.getADCValue());
        #endif
        //sum_tilt_angles += IMU.getTilt();  /* imu avarage does not work! */
        cnt--;                             
    }
    cnt = N_SAMPLES;  

    // Calculate final averages
    float avg_ir_distance = sum_ir_distaces / N_SAMPLES;    
    //float tilt_angle = sum_tilt_angles / N_SAMPLES; /* imu avarage does not work! */
    //Serial.println("Tilt angle = " + String(tilt_angle) + " °"); /* imu avarage does not work! */

    float IMU_tilt = IMU.getTilt();
    Serial.println("IMU sensor tilt " + String(IMU_tilt) + " °");
    //float final_value2 = sensorFusionSimplified(tiltCompensation(avg_ultr_distance, IMU_tilt), tiltCompensation(avg_ir_distance, IMU_tilt));
    float final_value = sensorFusion(tiltCompensation(avg_ultr_distance, IMU_tilt), tiltCompensation(avg_ir_distance, IMU_tilt));
    Serial.println("Estimated distance = " + String(final_value) + " mm*e-1");

    // BLE implementation
    ble.writeValue((uint32_t)final_value);
    float other_group_distance = ble.readValue(); 
    if (other_group_distance != 0) {
        Serial.println("BLE reads : " + String(other_group_distance));
    }

    delay(1000);
}


float sensorFusion(float ultr_measurement, float ir_measurement){
    if(ir_measurement < IR_SENSOR_THRESHOLD){
        return ir_measurement;
    }
    else if(ir_measurement > ULTR_SENSOR_THRESHOLD){
        return ultr_measurement;
    }
    else{
        //Performs weighted average for regions where no sensor dominates
        //where ir_weight + ultr_weight = 1
        float ir_weight = -1/(ULTR_SENSOR_THRESHOLD - IR_SENSOR_THRESHOLD)*ir_measurement + 1/(ULTR_SENSOR_THRESHOLD - IR_SENSOR_THRESHOLD)*IR_SENSOR_THRESHOLD;
        float ultr_weight = 1-ir_weight;
        return ir_weight*ir_measurement + ultr_weight*ultr_measurement;
    }
}

float tiltCompensation(float distance, float angle_deg){
    static float angle_rad = angle_deg * DEG_TO_RAD;
    if (cos(angle_rad) < 0) {
        Serial.println("Watch out: tilt angle exceeds 180°");
        return -1;
    } else {
        return distance*cos(angle_rad);
    } 
}