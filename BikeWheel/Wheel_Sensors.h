#pragma once
#include "Helpers.h"

namespace Wheel_Sensors {
    extern uint16_t angle;
    extern int32_t rotation_rate;

    void update() OPTIMIZE;
    void init();
};