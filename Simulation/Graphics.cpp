#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Graphics.h"
#include "Shader.h"
#include "FrameBuffer.h"

using namespace std;

namespace Graphics {
    // settings
    const unsigned int  SCR_WIDTH = 600, SCR_HEIGHT = 600;

    static GLFWwindow* window;
    static GLuint ledsVAO, ledsVBO;
    static Shader *ledsShader, *screen_shader;
    static FrameBuffer *screen_frame, *accum_frame;

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

        // Global Settings
        glPointSize(5.0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        ledsShader = new Shader("leds.vs", "leds.fs");

        glGenVertexArrays(1, &ledsVAO);
        glGenBuffers(1, &ledsVBO);

        glBindVertexArray(ledsVAO);
        glBindBuffer(GL_ARRAY_BUFFER, ledsVBO);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // screen quad VAO
        screen_shader = new Shader("screen.vs", "screen.fs");
        screen_frame = new FrameBuffer(SCR_WIDTH, SCR_HEIGHT);
        accum_frame = new FrameBuffer(SCR_WIDTH, SCR_HEIGHT);
        
        return true;
    }

    void clear() {
        delete screen_frame;
        delete accum_frame;
        screen_frame = new FrameBuffer(SCR_WIDTH, SCR_HEIGHT);
        accum_frame = new FrameBuffer(SCR_WIDTH, SCR_HEIGHT);
        glClearColor(0.0, 0.0, 0.0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    bool render(GLsizeiptr size, const void *data) {
        processInput();

        if (glfwWindowShouldClose(window)) {
            return false;
        }

        // bind to framebuffer and draw scene as we normally would to color texture 
        glBindFramebuffer(GL_FRAMEBUFFER, screen_frame->FBO);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the accum blur behind the scene
        screen_shader->use();
        screen_shader->setFloat("Alpha", 0.99);
        accum_frame->draw();

        glBindVertexArray(ledsVAO);

        ledsShader->use();
        glBindBuffer(GL_ARRAY_BUFFER, ledsVBO);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glDrawArrays(GL_POINTS, 0, size / (sizeof(float) * 5));

        // copy the scene to the accum blur
        glBindFramebuffer(GL_FRAMEBUFFER, accum_frame->FBO);
        screen_shader->use();
        screen_frame->draw();

        // now bind back to default framebuffer and draw a quad plane 
        // with the attached accum framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        glClearColor(0.0, 0.0, 0.0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        screen_shader->use();
        screen_shader->setFloat("Alpha", 1.0);
        accum_frame->draw();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // poll IO events (keys pressed/released, mouse moved etc.)
        glfwPollEvents();

        return true;
    }

    void terminate() {
        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        
        glDeleteVertexArrays(1, &ledsVAO);
        glDeleteBuffers(1, &ledsVBO);
        glfwTerminate();
    }
}
