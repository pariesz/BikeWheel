#pragma once
#include "arduino.h"

namespace Mpu {
    extern uint16_t angle;
    void init();
    void update();
};

