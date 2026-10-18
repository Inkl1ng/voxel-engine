#pragma once

#include <cstdint>
#include <map>
#include <functional>

#include <GLFW/glfw3.h>

#include "Player.hpp"

enum class Command {
    jump
};


class Input_handler {
public:
    Input_handler(GLFWwindow* window, Player& player);

    void add_keybind(int key, std::function<void()> cmd);
    void remove_keybind();

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos);

private:
    std::map<int, std::function<void()>> m_keybinds;
    float last_x_pos;
    float last_y_pos;
    Player& m_player;
};
