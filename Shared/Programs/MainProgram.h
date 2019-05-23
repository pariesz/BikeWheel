#pragma once

#include "../Program.h"
#include "../Logging.h"

#include "Color.h"
#include "Hamster.h"
#include "Kaleidoscope.h"
#include "LaPandora.h"
#include "MasaCritica.h"
#include "NyanCat.h"
#include "Radioactive.h"
#include "ExplodingText.h"
#include "Spiral.h"
#include "Velocity.h"
#include "ShootingStars.h"
#include "Portal.h"
#include "Rays.h"

#include "../Images/Fist.h"
#include "../Images/Poo.h"

class MainProgram : public Program {
private:
    bool on = 0;
    uint8_t index = 0;
    Program* program = new Color(COLOR_BLACK);

private:
    Program* start_program(int32_t rotation_rate) {
        log_val("program", index);

        switch (index) {
            case 0: return new Spiral;
            case 1: return new LaPandora;
            case 2: return new MasaCritica;
            case 3: return new Fist;
            case 4: return new ExplodingText(37, "- BCN - Critical Mass - Masa Critica");
            case 5: return new NyanCat;
            case 6: return new Poo;
            case 7: return new Velocity;
            case 8: return new Hamster;
            case 9: return new Portal;
            case 10: return new Rays;
            case 11: return new ShootingStars;
        }

        // loop back around
        index = rotation_rate < 0 ? 11 : 0;
        return start_program(rotation_rate);
    }

public:
    MainProgram() { }

    MainProgram(uint8_t index)
        : index(index)
        , on(1) {
    }

    void render(uint16_t zero_angle, int32_t rotation_rate) {
        if (on) {
            if (abs(rotation_rate) < 60000) {
                // too slow
                delete program;
                program = new Color(COLOR_BLACK);
                on = false;
            }
        } else {
            if (abs(rotation_rate) > 80000) {
                if (rotation_rate < 0) {
                    --index;
                } else {
                    ++index;
                }

                log_val("program", index);

                delete program;
                program = start_program(rotation_rate);
                on = true;
            }
        }

        program->render(zero_angle, rotation_rate);

    }
};