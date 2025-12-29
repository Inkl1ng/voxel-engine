#include "App.hpp"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Chunk.hpp"
#include "Shader.hpp"

App::App()
{
    // GLFW and window initialization
    glfwInit();
    // using version 4.3 so that we can use GLFW_OPENGL_DEBUG_CONTEXT for easier debugging
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef NDEBUG
    // nondebug
#else
    // debug code
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

    m_window = glfwCreateWindow(800, 600, "Voxel engine", NULL, NULL);
    if (m_window == NULL) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        std::exit(-1);
    }
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        glfwTerminate();
        std::exit(-1);
    }

    glViewport(0, 0, 800, 600);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

App::~App()
{
    glfwTerminate();
}

void App::run()
{
    Shader shader("shaders/triangle.vert", "shaders/triangle.frag");
    Chunk chunk;

    // main loop
    while (!glfwWindowShouldClose(m_window)) {
        poll_events();

        glClear(GL_COLOR_BUFFER_BIT);
        
        shader.use();
        chunk.draw();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void App::poll_events()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, true);
    }
}
