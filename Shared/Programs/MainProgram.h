#pragma once

#include "../Program.h"
#include "../Logging.h"

#include "Hamster.h"
#include "Kaleidoscope.h"
#include "LaPandora.h"
#include "MasaCritica.h"
#include "NyanCat.h"
#include "Radioactive.h"
#include "ExplodingText.h"
#include "Kaleidoscope.h"
#include "Spiral.h"
#include "Velocity.h"
#include "ShootingStars.h"
#include "Portal.h"
#include "Rays.h"
#include "Specs.h"
#include "TestSegments.h"

#include "../Images/MrSplat.h"
#include "../Images/finger.h"
#include "../Images/Fist.h"
#include "../Images/Poo.h"

class Transition : public Program {
    private:
        Program* program;
        uint8_t index;
        bool in;

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

enum MainProgramState {
    off = 0,
    on = 1,
    transitionIn = 2,
    transitionOut = 3
};

class MainProgram : public Program {
private:
    MainProgramState state;
    uint8_t index = 0;
    Program* program = nullptr;

private:
    Program* get_program(int32_t rotation_rate) {
        log_val("program", index);

        switch (index) {
            case  0: return new Spiral;
            case  1: return new LaPandora;
            case  2: return new MasaCritica;
            case  3: return new Fist;
            case  4: return new ExplodingText(37, "- BCN - Critical Mass - Masa Critica");
            case  5: return new NyanCat;
            case  6: return new Poo;
            case  7: return new Velocity;
            case  8: return new Hamster;
            case  9: return new Portal;
            case 10: return new Rays;
            case 11: return new ShootingStars;
        }

        // loop back around
        index = rotation_rate < 0 ? 11 : 0;
        return get_program(rotation_rate);
    }

    inline bool use_transition() {
        switch (index) {
            case  4: return false;
            case  9: return false;
            case 10: return false;
            case 11: return false;
            default: return true;
        }
    }

public:
    MainProgram()
        : state(off)
        , program(new Program) {
    }

    MainProgram(uint8_t index)
        : index(index)
        , state(on)
        , program(get_program(0)) {
    }

    void update(uint16_t frame_count, int32_t rotation_rate) override {
        switch (state) {
            case on: {
                if (abs(rotation_rate) < 60000) {
                    // too slow
                    program = new Transition(program, false);
                    state = transitionOut;
                }
                break;
            }
            case off: {
                if (abs(rotation_rate) > 80000) {
                    rotation_rate < 0 ? --index : ++index;

                    log_val("program", (int)index);

                    delete program;

                    Program* next_program = get_program(rotation_rate);

                    if (use_transition()) {
                        program = new Transition(next_program, true);
                        state = transitionIn;
                    } else {
                        program = next_program;
                        state = on;
                    }
                }
                break;
            }
            case transitionIn: {
                Transition* transition = (Transition*)program;

                if (transition->finished()) {
                    program = transition->get_program();
                    delete transition;
                    state = on;
                }
                break;
            }
            case transitionOut: {
                if (((Transition*)program)->finished()) {
                    delete program;
                    program = new Program;
                    state = off;
                    Leds::clear();
                }
                break;
            }
        }

        program->update(frame_count, rotation_rate);
    };

    inline void render(uint16_t zero_angle) {
        program->render(zero_angle);
    }
};