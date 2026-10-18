#pragma once

#include <cstdint>
#include <map>
#include <functional>

#include <GLFW/glfw3.h>

enum class Command {
    jump
};


class Input_handler {
public:
    Input_handler(GLFWwindow* window);

    void add_keybind(int key, std::function<void()> cmd);
    void remove_keybind();

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    std::map<int, std::function<void()>> m_keybinds;
};
