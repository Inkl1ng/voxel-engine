#include "Input_handler.hpp"

#include <cassert>
#include <bitset>
#include <iostream>

#include <GLFW/glfw3.h>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto input_handler = reinterpret_cast<Input_handler*>(glfwGetWindowUserPointer(window));
    input_handler->key_callback(window, key, scancode, action, mods);
}

void initialize_glfw_callbacks(GLFWwindow* window, Input_handler* i)
{
    glfwSetWindowUserPointer(window, i);
    glfwSetKeyCallback(window, key_callback);
}

void Input_handler::add_keybind(int key, int mods, Command cmd)
{
    // Here the bits for the key and mods are combined into one int16.
    // This is done to use a built-in-type instead of a struct. Using a struct would require
    // doing operator overloading to make it work in an std::map.
    // The bits for the key are shifted 3 over to make space for the three mod keys.
    int16_t combined = (key << 3) + mods;
    std::cout << std::bitset<16>(combined) << '\n';
    std::cout << (combined >> 3) << '\n';

    m_keybinds[combined] = cmd;
}

void Input_handler::remove_keybind()
{
}

void Input_handler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    return;
}

