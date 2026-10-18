#include "Input_handler.hpp"

#include <cassert>
#include <bitset>
#include <iostream>
#include <functional>

#include <GLFW/glfw3.h>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // the user pointer is a void pointer so we have to cast it like this
    auto input_handler = reinterpret_cast<Input_handler*>(glfwGetWindowUserPointer(window));
    // reroute the data to the Input_handler instance
    input_handler->key_callback(window, key, scancode, action, mods);
}

void initialize_glfw_callbacks(GLFWwindow* window, Input_handler* i)
{
    // use a user pointer to to be able to route the info from key_callback into an insantce
    glfwSetWindowUserPointer(window, i);
    glfwSetKeyCallback(window, key_callback);
}

void Input_handler::add_keybind(int key, std::function<void()> cmd)
{
    m_keybinds[key] = cmd;
}

void Input_handler::remove_keybind()
{
}

void Input_handler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const bool is_binded{ m_keybinds.find(key) != m_keybinds.end() };
    if (is_binded) {
        m_keybinds[key]();
    }
}
