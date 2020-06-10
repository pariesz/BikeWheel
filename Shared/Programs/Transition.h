#pragma once
#include "Program.h"

class Transition : public Program {
private:
    Program* program;
    bool in;
    bool up;
    uint8_t index;

public:
    Transition(Program* program, bool in)
        : program(program)
        , in(in)
        , up(millis() % 2)
        , index(up ? 0 : LEDS_PER_STRIP - 1) {
    }

    Program* get_program() {
        return program;
    }

    inline bool finished() {
        return index == (up ? LEDS_PER_STRIP - 1 : 0);
    }

    void update(uint16_t frame_count, int32_t rotation_rate) override {
        program->update(frame_count, rotation_rate);
        up ? ++index : --index;
    }

    void render(uint16_t zero_angle) override {
        program->render(zero_angle);

        uint8_t* pixels = Leds::leds.getPixels();

        uint8_t length = 3 * (in ^ up ? (index + 1) : (LEDS_PER_STRIP - index - 1));

        for (uint8_t i = 0; i < LEDS_STRIPS_COUNT; i++) {
            uint16_t strip_index = i * LEDS_PER_STRIP;
            uint16_t transition_index = strip_index + index;
            uint16_t start_index = in ^ up ? strip_index : transition_index + 1;

            // Mask transitioning pixels black
            memset(pixels + (3 * start_index), 0, length);

            // Set the transition pixel to white
            memset(pixels + (3 * transition_index), 0xFF, 3);
        }
    }
};