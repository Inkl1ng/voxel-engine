#include "App.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Chunk.hpp"
#include "Shader.hpp"
#include "Player.hpp"

constexpr int window_width = 800;
constexpr int window_height = 600;

void APIENTRY gl_debug_message_callback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar *msg, const void *data)
{
    char* _source;
    char* _type;
    char* _severity;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;

        case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;

        case GL_DEBUG_SOURCE_OTHER:
        _source = "UNKNOWN";
        break;

        default:
        _source = "UNKNOWN";
        break;
    }

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR";
        break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UDEFINED BEHAVIOR";
        break;

        case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY";
        break;

        case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;

        case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER";
        break;

        case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;

        default:
        _type = "UNKNOWN";
        break;
    }

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
        break;

        case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        break;

        case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        break;

        default:
        _severity = "UNKNOWN";
        break;
    }

    printf("%d: %s of %s severity, raised from %s: %s\n",
            id, _type, _severity, _source, msg);
}

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
