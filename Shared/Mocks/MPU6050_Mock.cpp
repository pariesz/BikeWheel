#include "MPU6050_Mock.h"
#include "Arduino_Mock.h"

#if !defined(ARDUINO)
static int16_t _acc_x  = 0;
static int16_t _acc_y  = 0;
static int16_t _acc_z  = 0;
static int16_t _gyro_x = 0;
static int16_t _gyro_y = 0;
static int16_t _gyro_z = 0;

MPU6050::MPU6050(int addr) { }

void MPU6050::setMotion6(int16_t acc_x, int16_t acc_y, int16_t acc_z, int16_t gyro_x, int16_t gyro_y, int16_t gyro_z) {
    _acc_x  = acc_x;
    _acc_y  = acc_y;
    _acc_z  = acc_z;
    _gyro_x = gyro_x;
    _gyro_y = gyro_y;
    _gyro_z = gyro_z;
}

void MPU6050::getMotion6(int16_t *acc_x, int16_t *acc_y, int16_t *acc_z, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z) {
    *acc_x  = _acc_x;
    *acc_y  = _acc_y;
    *acc_z  = _acc_z;
    *gyro_x = _gyro_x;
    *gyro_y = _gyro_y;
    *gyro_z = _gyro_z;
}

void MPU6050::getAcceleration(int16_t* x, int16_t* y, int16_t* z) {
    *x = _acc_x;
    *y = _acc_y;
    *z = _acc_z;
}
#endif