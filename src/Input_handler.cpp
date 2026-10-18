#include "Input_handler.hpp"

#include <cassert>
#include <bitset>
#include <iostream>
#include <functional>

#include <GLFW/glfw3.h>


static Input_handler* get_input_handler_pointer(GLFWwindow* window)
{
    return reinterpret_cast<Input_handler*>(glfwGetWindowUserPointer(window));
}

static void static_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    get_input_handler_pointer(window)->key_callback(window, key, scancode, action, mods);
}

static void static_cursor_position_callback(GLFWwindow* window,  double x_pos, double y_pos)
{
    //get_input_handler_pointer(window)->cursor_position_callback(window, x_pos, y_pos);
}

Input_handler::Input_handler(GLFWwindow* window)
{
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, static_key_callback);
    glfwSetCursorPosCallback(window, static_cursor_position_callback);
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
    const bool is_binded = m_keybinds.find(key) != m_keybinds.end();
    if (is_binded) {
        m_keybinds[key]();
    }
}
