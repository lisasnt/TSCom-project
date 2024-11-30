#include "SensorFusion.h"

float tiltComp(distance, angle){
    //Have to assume that system is placed close to horizontaly
    return distance * cos(angle);
}

int colorDetect(Ultra_sound_dsitance, infrared_measurment){
    /*
        Based on the measurment from the Ultra Sound, we want to figure out what color best represents the infrared_measurment
        Alternatively; Have user place the measured object in a fixed distance to callibrate the sensor. (Recomended by teacher)
    */
}

float colorComp(v_infra, d_ultra, d_ultra_treshold, v_infra_treshold, &color_comp){
    /*
        Need curves for different color(Teacher reccomended like 3)
        Use the curves to predict distance based on recived voltage
    */

    if(d_ultra < d_ultra_treshold){
        Serial.print("Warning: Infrared is not calibrated correclty due to distance to object being to short.")
    }else if(v_infra < v_infra_treshold){
        Serial.print("Warning: Infrared is not calibrated correclty due recvied signal is to weak.")
    }else{
        return color_comp
    }

}

float predDistance(d_ultra, d_infra, w_utlra, w_infra){
    /*
        Create a system for weighing the differnet measurments
        Idea(Not necceceraly optimal): Find probability of each measurment being the right one, and find expected value based on this
    */

    return w_ultra*d_ultra-w_infra*d_infra/(w_ultra + w_infra);

}