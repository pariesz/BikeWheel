#pragma once
#include "Program.h"

class Transition : public Program {
private:
    Program* program;
    bool in;
    uint8_t index;

public:
    Transition(Program* program, bool in)
        : program(program)
        , in(in)
        , index(in ? 0 : LEDS_PER_STRIP - 1) {
    }

    Program* get_program() {
        return program;
    }

    inline bool finished() {
        return index == (in ? LEDS_PER_STRIP - 1 : 0);
    }

    void update(uint16_t frame_count, int32_t rotation_rate) override {
        program->update(frame_count, rotation_rate);
        in ? ++index : --index;
    }

    void render(uint16_t zero_angle) override {
        program->render(zero_angle);

        uint8_t* pixels = Leds::leds.getPixels();
        uint8_t length = (LEDS_PER_STRIP - index - 1) * 3;

        for (uint8_t i = 0; i < LEDS_STRIPS_COUNT; i++) {
            uint16_t strip_index = index + (i * LEDS_PER_STRIP);
            memset(pixels + (3 * (strip_index + 1)), 0, length);
            memset(pixels + (3 * strip_index), 0xFF, 3);
        }
    }

    ~Transition() {
        if (!in) {
            delete program;
        }
    }
};