#pragma once
#include "./Vector.h"
#define OPTIMIZE __attribute__((optimize("O3")))

/*
 * Orientation of MPU6050 (Accelerometer / Gyroscope)
 * Should match the axis of the Axel
 *   1 == X
 *   2 == Y
 *   3 == Z
 */
#define ORIENTATION 2

// MPU6050 is in the reverse direction
#define REVERSE false

#define DEGS_TO_ANGLE(x) (uint16_t)((x) / 180.0f * (1uLL << 15))

#define DEGS_PER_S_TO_RATE(x) (uint16_t)((x) * 16.4f)

namespace Gyro {
    extern uint16_t angle;

    void init(void);
    void update(void) OPTIMIZE;
};