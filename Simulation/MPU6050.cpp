#include "MPU6050.h"
#include "arduino.h"
#include "SensorData.h"

MPU6050::MPU6050(int addr) {
    
}

void MPU6050::getMotion6(int16_t *acc_x, int16_t *acc_y, int16_t *acc_z, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z) {
    auto line = SensorData::get();

    *acc_x  = line.acc_x;
    *acc_y  = line.acc_y;
    *acc_z  = line.acc_z;
    *gyro_x = line.gyro_x;
    *gyro_y = line.gyro_y;
    *gyro_z = line.gyro_z;
}

void MPU6050::getAcceleration(int16_t* x, int16_t* y, int16_t* z) {
    auto line = SensorData::get();

    *x = line.acc_x;
    *y = line.acc_y;
    *z = line.acc_z;
}

void MPU6050::getRotation(int16_t* x, int16_t* y, int16_t* z) {
    auto line = SensorData::get();

    *x = line.gyro_x;
    *y = line.gyro_y;
    *z = line.gyro_z;
}

MPU6050::~MPU6050() {

}
