#pragma once
#include "Program.h"

class Off : public Program {

public:
    void update(uint16_t frame_count, int32_t rotation_rate) override {
        Leds::clear();
    }
};