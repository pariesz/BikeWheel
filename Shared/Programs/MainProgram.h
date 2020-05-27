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
#include "Transition.h"

#include "../Images/MrSplat.h"
#include "../Images/finger.h"
#include "../Images/Fist.h"
#include "../Images/Poo.h"

enum MainProgramState {
    off = 0,
    on = 1,
    transitionIn = 2,
    transitionOut = 3
};

class MainProgramSettings {
public:
    uint32_t onRotationRate = 80000;
    uint32_t offRotationRate = 60000;
    const char* explodingText = " - BCN - Critical Mass - Test Critica";
    uint8_t program = 0;
};

class MainProgram : public Program {
private:
    MainProgramState state = off;
    uint8_t index = 3;
    Program* programPtr = new Program;
    MainProgramSettings* settingsPtr;

private:
    Program* get_program(int32_t rotation_rate) {
        log_val("program", index);

        switch (index) {
            case  0: return new Spiral;
            case  1: return new LaPandora;
            case  2: return new MasaCritica;
            case  3: return new Fist;
            case  4: return new ExplodingText(settingsPtr->explodingText);
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
    MainProgram(MainProgramSettings* settings)
        : settingsPtr(settings) {
    }

    void update(uint16_t frame_count, int32_t rotation_rate) override {
        switch (state) {
            case on: {
                if (abs(rotation_rate) < 60000) {
                    // too slow
                    programPtr = new Transition(programPtr, false);
                    state = transitionOut;
                }
                break;
            }
            case off: {
                if (abs(rotation_rate) > 80000) {
                    rotation_rate < 0 ? --index : ++index;

                    log_val("program", (int)index);

                    delete programPtr;

                    Program* next_program = get_program(rotation_rate);

                    if (use_transition()) {
                        programPtr = new Transition(next_program, true);
                        state = transitionIn;
                    } else {
                        programPtr = next_program;
                        state = on;
                    }
                }
                break;
            }
            case transitionIn: {
                Transition* transition = (Transition*)programPtr;

                if (transition->finished()) {
                    programPtr = transition->get_program();
                    delete transition;
                    state = on;
                }
                break;
            }
            case transitionOut: {
                if (((Transition*)programPtr)->finished()) {
                    delete programPtr;
                    programPtr = new Program;
                    state = off;
                    Leds::clear();
                }
                break;
            }
        }

        programPtr->update(frame_count, rotation_rate);
    };

    inline void render(uint16_t zero_angle) {
        programPtr->render(zero_angle);
    }
};