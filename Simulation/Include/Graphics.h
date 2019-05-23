#pragma once
#include <GLFW/glfw3.h>
#include "Leds.h"

namespace Graphics {
    extern float vertices[LEDS_COUNT * 5];
    bool init();
    void clear();
    bool render();
    void terminate();
};