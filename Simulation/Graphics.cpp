#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Graphics.h"
#include "Shaders.h"

using namespace std;

namespace Graphics {
    // settings
    const unsigned int SCR_WIDTH = 600;
    const unsigned int SCR_HEIGHT = 600;

    GLFWwindow* window;
    GLuint VAO, VBO, FBO;

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput() {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    bool init() {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Bike Wheel Simulation", NULL, NULL);

        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        Shaders::init();

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenFramebuffers(1, &FBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(Shaders::positionAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glVertexAttribPointer(Shaders::colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(Shaders::positionAttrib);
        glEnableVertexAttribArray(Shaders::colorAttrib);
        glBindBuffer(GL_ARRAY_BUFFER, 0);



        
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        unsigned int RBO;
        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO); // now actually attach it

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        return true;
    }
    int n = 2;
    int i = 0;

    bool render(GLsizeiptr size, const void *data) {
        processInput();

        if (glfwWindowShouldClose(window)) {
            return false;
        }


        // render
        // ------
        glClearColor(0.1, 0.1, 0.1, 0.2);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glDrawArrays(GL_POINTS, 0, size / (sizeof(float) * 5));

        GLint buffer_size;
        glBindBuffer(GL_COPY_WRITE_BUFFER, FBO);
        glGetBufferParameteriv(GL_BACK, GL_BUFFER_SIZE, &buffer_size);
        glCopyBufferSubData(GL_BACK, GL_COPY_WRITE_BUFFER, 0, 0, buffer_size);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // poll IO events (keys pressed/released, mouse moved etc.)
        glfwPollEvents();

        return true;
    }

    void terminate() {
        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteFramebuffers(1, &FBO);
        glfwTerminate();
    }
}
