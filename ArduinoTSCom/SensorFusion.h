#ifndef SENSOR_FUSION_H
#define SENSOR_FUSION_H

#define T_INFRA     7.5
#define T_ULTRA     14.5
#define DEG_TO_RAD  0.0174533 

float sensorFusion(float d_ultra, float d_infra);
float tiltComp(float distance, float angle);

#endif