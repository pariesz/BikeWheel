#include "Programs.h"

#include "Programs/Hamster.h"
#include "Programs/Kaleidoscope.h"
#include "Programs/LaPandora.h"
#include "Programs/MasaCritica.h"
#include "Programs/NyanCat.h"
#include "Programs/Radioactive.h"
#include "Programs/ExplodingText.h"
#include "Programs/Kaleidoscope.h"
#include "Programs/Spiral.h"
#include "Programs/Velocity.h"
#include "Programs/ShootingStars.h"
#include "Programs/Portal.h"
#include "Programs/Rays.h"
#include "Programs/Specs.h"
#include "Programs/TestSegments.h"
#include "Programs/Transition.h"
#include "Programs/PulseProgram.h"
#include "Programs/Rainbow.h"
#include "Programs/Off.h"
#include "Programs/TimerProgram.h"

#include "Images/MrSplat.h"
#include "Images/finger.h"
#include "Images/Fist.h"
#include "Images/Poo.h"

namespace Programs {
    Program* get_program(uint8_t index, bool moving) {
        if (index == PROGRAM_TIMER) {
            return new TimerProgram(moving);
        }
        else if (moving) {
            switch (index) {
            case  2: return new MasaCritica;
            case  3: return new Fist;
            case  4: return new ExplodingText;
            case  5: return new NyanCat;
            case  6: return new Poo;
            case  7: return new Velocity;
            case  8: return new Hamster;
            case  9: return new Portal;
            case 10: return new Rays;
            case 11: return new ShootingStars;
            case 12: return new Spiral;
            case 13: return new LaPandora;
            case 14: return new Radioactive;
            }
        }
        else {
            switch (index) {
            case 2: return new PulseProgram;
            case 3: return new Rainbow;
            }
        }

        return new Off;
    }

    bool use_in_transition(uint8_t index, bool moving) {
        switch (index) {
            case  PROGRAM_OFF:
            case  PROGRAM_TIMER: return false;
            case  2: return moving;
            case  4:
            case  9:
            case 10: 
            case 11: return !moving;
            default: return true;
        }
    }
}