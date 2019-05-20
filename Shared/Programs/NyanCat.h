#pragma once
#include "../Images/NyanCat1.h"
#include "../Images/NyanCat2.h"
#include "../Program.h"

class NyanCat : public Program {

private:
    NyanCat1 frame1;
    NyanCat2 frame2;

public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        // Whoops, Images are in reverse.
        rotation_rate = -rotation_rate;

        if (millis() & (1 << 9)) {
            frame1.render(zero_angle, rotation_rate);
        } else {
            frame2.render(zero_angle, rotation_rate);
        }
    }
};