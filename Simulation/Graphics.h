#pragma once
#include <GLFW/glfw3.h>

namespace Graphics {
    bool init();
    bool render(GLsizeiptr size, const void *data);
    void terminate();
};

