#include "SensorFusion.h"
/*
float tiltComp(distance, angle){
    //Have to assume that system is placed close to horizontaly
    return distance * cos(angle);
}

float colorDetect(v_infra, d_ultra){
    
        Finds the color and returns the offset corresponding to that color.
    
}
*/
/*
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
*/
float measurmentToDistance(float v_infra){
    /*
        Should transform v_infra to d_infra
    */
        return 1.55058830e-02 * v_infra 
           -1.07071156e-05 * pow(v_infra, 2) 
           + 6.27489604e-01 * pow((1 / (v_infra) )* 1000, 2) 
           -5.377095188616198;
}


float sensorFusion(float d_ultra, float d_infra){
    float t_infra = 7.5;
    float t_ultra = 14.5;
    if(d_infra < t_infra){
        return d_infra;
    }
    else if(d_infra > t_ultra){
        return d_ultra;
    }
    else{
        //Preforms weighted average for regions bewteen areas where one sensor dominates
        //w_infra and w_ultra are between 0 and 1
        float w_infra = -1/(t_infra-t_ultra)*d_infra + 1/(t_infra-t_ultra)*t_infra;
        float w_ultra = 1-w_infra;
        return w_infra*d_infra + w_ultra*d_ultra;
    }
}
