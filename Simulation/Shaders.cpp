#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shaders.h"

namespace Shaders {

    GLint positionAttrib;

    GLint colorAttrib;

    const char *vertexShaderSource =
        "#version 330 core\n"

        "layout (location = 0) in vec2 position;\n"
        "layout (location = 1) in vec3 color;\n"
        "out vec3 interpColor;\n"

        "void main() {\n"
        "   gl_Position = vec4(position, 0.0, 1.0);\n"
        "   interpColor = color;\n"
        "}\0";

    const char *fragmentShaderSource =
        "#version 330 core\n"

        "in vec3 interpColor;\n"

        "void main() {\n"
        "   vec2 pos = gl_PointCoord - vec2(0.5);"
        "   float dist_squared = dot(pos, pos);"
        "   gl_FragColor = mix(vec4(interpColor, 1.0), vec4(0.1, 0.1, 0.1, 0.0), smoothstep(0.2, 0.3, dist_squared));"
        "}\0";

    int linkShaders(const int shaderA, const int shaderB) {
        int success;
        char infoLog[512];

        int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, shaderA);
        glAttachShader(shaderProgram, shaderB);
        glLinkProgram(shaderProgram);

        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        return shaderProgram;
    }

    int getShader(const GLchar *const *source, const int type) {
        int success;
        char infoLog[512];

        int shader = glCreateShader(type);
        glShaderSource(shader, 1, source, NULL);
        glCompileShader(shader);

        // check for shader compile errors
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        return shader;
    }

    void init() {
        glPointSize(5.0);

        int vertexShader = getShader(&vertexShaderSource, GL_VERTEX_SHADER);
        int fragmentShader = getShader(&fragmentShaderSource, GL_FRAGMENT_SHADER);

        int shaderProgram = linkShaders(vertexShader, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glUseProgram(shaderProgram);

        positionAttrib = glGetAttribLocation(shaderProgram, "position");
        colorAttrib = glGetAttribLocation(shaderProgram, "color");
    }
}
