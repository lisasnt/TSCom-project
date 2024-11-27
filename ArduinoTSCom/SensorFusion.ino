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

float colorComp(infrared_measurment){
    /*
        Need curves for different color(Teacher reccomended like 3)
        Use the curves to predict distance based on recived voltage
    */
}

float predDistance(Ultra_sound_distance, infrared_distance){
    /*
        Create a system for weighing the differnet measurments
        Idea(Not necceceraly optimal): Find probability of each measurment being the right one, and find expected value based on this
    */
}