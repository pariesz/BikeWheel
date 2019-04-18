#pragma once
#include "arduino.h"

#define MPU6050_DEFAULT_ADDRESS 0

class MPU6050 {
    public:
        MPU6050(int addr);
        void getMotion6(int16_t *accx, int16_t *accy, int16_t *accz, int16_t *gyrox, int16_t *gyroy, int16_t *gyroz);
        void getAcceleration(int16_t *accx, int16_t *accy, int16_t *accz);
        ~MPU6050();
};
