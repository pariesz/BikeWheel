#pragma once
#include "Program.h"

class Off : public Program {

public:
    void update(int32_t rotation_rate) override {
        Leds::clear();
    }
};