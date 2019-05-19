#pragma once

#include "NyanCat1.h"
#include "NyanCat2.h"

class NyanCat {
private:
    NyanCat1 frame1;
    NyanCat2 frame2;
public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        if (millis() & (1 << 9)) {
            frame1.render(zero_angle, rotation_rate);
        } else {
            frame2.render(zero_angle, rotation_rate);
        }
    }
};