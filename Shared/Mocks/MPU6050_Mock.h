#pragma once
#if defined(ARDUINO) && ARDUINO >= 100
    #include <MPU6050.h>
#else
#include "Arduino_Mock.h"

#define MPU6050_DEFAULT_ADDRESS 0

class MPU6050 {
    public:
        MPU6050(int addr);
        static void setMotion6(int16_t accx, int16_t accy, int16_t accz, int16_t gyrox, int16_t gyroy, int16_t gyroz);
        void getMotion6(int16_t *accx, int16_t *accy, int16_t *accz, int16_t *gyrox, int16_t *gyroy, int16_t *gyroz);
        void getAcceleration(int16_t *accx, int16_t *accy, int16_t *accz);
};
#endif