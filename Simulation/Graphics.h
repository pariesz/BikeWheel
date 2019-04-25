#pragma once
#include <GLFW/glfw3.h>

namespace Graphics {
    bool init();
    void clear();
    bool render(GLsizeiptr size, const void *data);
    void terminate();
};

