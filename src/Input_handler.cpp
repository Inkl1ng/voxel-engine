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
    get_input_handler_pointer(window)->cursor_position_callback(window, x_pos, y_pos);
}

Input_handler::Input_handler(GLFWwindow* window, Player& player)
    : m_player (player)
{
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, static_key_callback);
    glfwSetCursorPosCallback(window, static_cursor_position_callback);

    int window_width;
    int window_height;
    glfwGetWindowSize(window, &window_width, &window_height);
    last_x_pos = window_width / 2;
    last_y_pos = window_height / 2;
}

void Input_handler::add_keybind(int key, std::function<void()> cmd)
{
    m_keybinds[key] = cmd;
}

void Input_handler::remove_keybind()
{
    // TODO: implement
}

void Input_handler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const bool is_binded = m_keybinds.find(key) != m_keybinds.end();
    if (is_binded) {
        m_keybinds[key]();
    }
}

void Input_handler::cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos)
{
    constexpr float sensitivity = 0.01f;
    static bool first_run = true;

    const float x_offset = x_pos - last_x_pos;
    // without the multiplication moving the mouse pitches the camera up
    // most people are used to moving the mouse up to pitch the camera up
    const float y_offset = -1 * (y_pos - last_y_pos);
    if (first_run) {
        m_player.receive_cursor_offset(0.0f, 0.0f);
        first_run = false;
    }
    else {
        m_player.receive_cursor_offset(x_offset, y_offset);
    }

    last_x_pos = x_pos;
    last_y_pos = y_pos;
}
