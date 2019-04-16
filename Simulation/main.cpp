#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int getShader(const GLchar *const *source, const int type);
int linkShaders(const int shaderA, const int shaderB);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

GLFWwindow* window;

//     x,    y,   r,   g,   b
float vertices[] = {
    -0.5, -0.5, 1.0, 0.0, 0.0,
     0.5, -0.5, 0.0, 1.0, 0.0,
     0.0,  0.5, 0.0, 0.0, 1.0,
    -0.4, -0.4, 1.0, 0.0, 0.0,
     0.4, -0.4, 0.0, 1.0, 0.0,
     0.0,  0.4, 0.0, 0.0, 1.0
};

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Bike Wheel Simulation", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    glPointSize(10.0);

    int vertexShader = getShader(&vertexShaderSource, GL_VERTEX_SHADER);
    int fragmentShader = getShader(&fragmentShaderSource, GL_FRAGMENT_SHADER);

    int shaderProgram = linkShaders(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(shaderProgram);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Positions
    GLint positionAttrib = glGetAttribLocation(shaderProgram, "position");
    GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");

    glVertexAttribPointer(positionAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(colorAttrib,    3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

    glEnableVertexAttribArray(positionAttrib);
    glEnableVertexAttribArray(colorAttrib);

    int i = 0;
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        if (vertices[i] < 1) {
            vertices[i] = vertices[i] += 0.01f;
        }
        if (++i >= sizeof(vertices)) {
            i = 0;
        }

        double currentTime = glfwGetTime();
        
        nbFrames++;

        if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\n", 1000.0 / double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glDrawArrays(GL_POINTS, 0, sizeof(vertices) / (sizeof(float) * 5));

        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // poll IO events (keys pressed/released, mouse moved etc.)
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

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

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}