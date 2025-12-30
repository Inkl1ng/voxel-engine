#pragma once

#include <cstdint>
#include <map>

#include <GLFW/glfw3.h>

enum class Command {
    jump
};


class Input_handler {
public:
    void add_keybind(int key, int mods, Command cmd);
    void remove_keybind();

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    std::map<int16_t, Command> m_keybinds;
};

void initialize_glfw_callbacks(GLFWwindow* window, Input_handler* i);

