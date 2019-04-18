#include <math.h>
#include "MPU6050.h"
#include "Mpu.h"

namespace Mpu {
    uint16_t angle = 0;

    static MPU6050 mpu = MPU6050(MPU6050_DEFAULT_ADDRESS);

    void init() {

    }

    void update() {
        int16_t acc[3];

        mpu.getAcceleration(&acc[0], &acc[1], &acc[2]);

        angle = atan2(acc[0], acc[2] - 8000) * (-32768.0f / M_PI);
    }
}