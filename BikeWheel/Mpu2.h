#pragma once
#define OPTIMIZE __attribute__((optimize("O3")))

namespace Mpu2 {
    void init(Vector3<int16_t> &accelOffset, Vector3<int16_t> &gyroOffset);
    void update();
}