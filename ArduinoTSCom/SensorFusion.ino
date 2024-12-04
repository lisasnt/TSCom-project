#include "SensorFusion.h"

float sensorFusion(float d_ultra, float d_infra){
    if(d_infra < T_INFRA){
        return d_infra;
    }
    else if(d_infra > T_ULTRA){
        return d_ultra;
    }
    else{
        //Preforms weighted average for regions bewteen areas where one sensor dominates
        //w_infra and w_ultra are between 0 and 1
        float w_infra = -1/(T_ULTRA - T_INFRA)*d_infra + 1/(T_ULTRA - T_INFRA)*T_INFRA;
        float w_ultra = 1-w_infra;
        return w_infra*d_infra + w_ultra*d_ultra;
    }
}

float tiltComp(float distance, float angle_deg){
    static float angle_rad = angle_deg * DEG_TO_RAD;
    if (cos(angle_rad) < 0) {
        Serial.println("Watch out: tilt angle exceeds 180°");
        return -1;
    } else {
        return distance*cos(angle_rad);
    } 
}