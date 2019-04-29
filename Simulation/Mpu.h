#pragma once
#include "Arduino.h"

namespace Mpu {
    extern uint16_t angle;
    extern int32_t rotation_rate;
    void update();
    void init();
}