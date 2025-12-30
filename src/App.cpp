#include "App.hpp"

#include <cstddef>
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Chunk.hpp"
#include "Input_handler.hpp"
#include "debug.hpp"
#include "Shader.hpp"
#include "Player.hpp"

constexpr int window_width = 800;
constexpr int window_height = 600;

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

    m_window = glfwCreateWindow(window_width, window_height, "Voxel engine", NULL, NULL);
    if (m_window == NULL) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        std::exit(-1);
    }
    glfwMakeContextCurrent(m_window);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        glfwTerminate();
        std::exit(-1);
    }

    glViewport(0, 0, 800, 600);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(gl_debug_message_callback, NULL);
}

App::~App()
{
    glfwTerminate();
}

void App::run()
{
    Input_handler input_handler;
    initialize_glfw_callbacks(m_window, &input_handler);
    input_handler.add_keybind(GLFW_KEY_MENU, GLFW_MOD_SHIFT, Command::jump);
    Shader shader("shaders/triangle.vert", "shaders/triangle.frag");
    Chunk chunk;
    Player player(glm::vec3(0.0f, 0.0f, -3.0f));

    // main loop
    while (!glfwWindowShouldClose(m_window)) {
        poll_events();

        glClear(GL_COLOR_BUFFER_BIT);

        constexpr float aspect_ratio = static_cast<float>(window_width) / static_cast<float>(window_height);
        glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect_ratio, 0.1f, 100.0f);
        glm::mat4 view = glm::mat4(1.0f);
        view = translate(view, glm::vec3(0.0f, 1.0f, -1.5f));
        
        shader.use();

        shader.set_mat4("projection", projection);
        shader.set_mat4("view", view);
        
        //shader.set_mat4("view", player.get_view_matrix());

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
