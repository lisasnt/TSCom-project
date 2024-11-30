#include "SensorFusion.h"

float tiltComp(distance, angle){
    //Have to assume that system is placed close to horizontaly
    return distance * cos(angle);
}

float colorDetect(v_infra, d_ultra){
    /*
        Finds the color and returns the offset corresponding to that color.
    */
}


float infraToDistance(v_infra, infra_treshold, d_ultra, ultra_treshold){
    if(d_ultra < d_ultra_treshold){
        Serial.print("Warning: Infrared is not calibrated correclty due to distance to object being to short.");
        return 0;
    }else if(v_infra < v_infra_treshold){
        Serial.print("Warning: Infrared is not calibrated correclty due recvied signal is to weak.");
        return 0;
    }else{
        return measurmentToDistance(v_ultra) + colorDetect(v_infra, d_ultra);
    }
}

float measurmentToDistance(v_infra){
    /*
        Should transform v_infra to d_infra
    */
    return 0;
}

float distanceComb(d_ultra, d_infra){
    /*
        Preform sesnor fusion on the data, probably gonna use weighted average of some sort.
    */
}
