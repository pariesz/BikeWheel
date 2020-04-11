#pragma once
#include "../Images/NyanCat1.h"
#include "../Images/NyanCat2.h"
#include "../Program.h"

class NyanCat : public Program {

private:
    NyanCat1 frame1;
    NyanCat2 frame2;
    Image* frame = &frame1;
    uint8_t star_index = 0xFF;

public:
    inline uint32_t gray(uint8_t b) {
        return b << 16 | b << 8 | b;
    }

    void update(uint16_t frame_count, int32_t rotation_rate) override {
        frame = (frame_count & 0x10) ? (Image*)&frame1 : &frame2;
        frame->update(frame_count, ~rotation_rate);
    }

    inline void render_star(uint16_t zero_angle) {
        uint8_t index = random(0, LEDS_COUNT - 1);
        
        uint16_t angle = zero_angle + Leds::get_angle(index);
        
        double radians = (angle / (float)0xFFFF) * TWO_PI;

        int16_t y = Leds::get_distance(index) * cos(radians);

        // don't add stars over the cats body
        if (y < -0x70 || y > 0x80) {
            Leds::set_color(index, gray(random(0, 0xFF)));
        }
    }

    void render(uint16_t zero_angle) {
        frame->render(zero_angle);
        render_star(zero_angle);
    }
};