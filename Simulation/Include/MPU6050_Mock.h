#pragma once
#include "Arduino_Mock.h"

#define MPU6050_DEFAULT_ADDRESS 0

class MPU6050 {
    private:
        int16_t zAccelOffset = 0;

    public:
        MPU6050(int addr);
        void getMotion6(int16_t *accx, int16_t *accy, int16_t *accz, int16_t *gyrox, int16_t *gyroy, int16_t *gyroz);
        void getAcceleration(int16_t *accx, int16_t *accy, int16_t *accz);
        void getRotation(int16_t* x, int16_t* y, int16_t* z);
        void setZAccelOffset(int16_t offset);
        ~MPU6050();
};

