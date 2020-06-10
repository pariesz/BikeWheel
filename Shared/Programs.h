#pragma once
#include "Mocks/Arduino_Mock.h"
#include "Program.h"

#define PROGRAM_OFF   0
#define PROGRAM_TIMER 1
#define PROGRAM_MOVING_COUNT 15
#define PROGRAM_STATIONARY_COUNT 4 

namespace Programs {
    Program* get_program(uint8_t index, bool moving);

    // Programs that start empty (leds off) should not transition in
    bool use_in_transition(uint8_t index, bool moving);
}

