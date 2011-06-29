//Sensor Plate
//File: kalman.h
//Implements a basic Kalman Filter (32-bit floating point precision)
//Copyright C. Au and T. Zhang, 2010

#ifndef _KA_KALMAN_H_
#define _KA_KALMAN_H_ 1

typedef struct _kalman kalman;

struct _kalman
{
    // State estimation matrix.
    float x_00;
    float x_10;

    // Covariance of estimation error matrix.
    float P_00;
    float P_01;
    float P_10;
    float P_11;

    // State constants.
    float A_01;
    float B_00;
    float Sz_00;
    float Sw_00;
    float Sw_11;
};

// Initialize the kalman state.
void kalman_init(kalman *self, float dt, float Sz_00, float Sw_00, float Sw_11, float init_x_00, float init_x_10);

// Update the kalman state estimate and return the estimated angle.
float kalman_update(kalman *self, float gyro_rate, float accel_angle);

#endif // _KA_KALMAN_H_