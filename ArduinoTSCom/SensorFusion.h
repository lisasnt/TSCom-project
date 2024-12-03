#pragma once
#include "math.h"
//float tiltComp(distance, angle);


//Should find out what color is most likely to be reflecting. 

//float colorComp(v_infra, d_ultra);
//float infraToDistance(v_infra, infra_treshold, d_ultra, ultra_treshold);
float measurmentToDistance(float v_ultra);
float sensorFusion(float d_ultra, float d_infra);
//float distanceComb(d_ultra, d_infra);


