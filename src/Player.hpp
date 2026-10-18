#pragma once

#include <array>

#include <glm/glm.hpp>

class Player {
public:
    enum Movement {
        forward,
        backward,
        left,
        right,
        up,
        down,
        null
    };

public:
    Player(glm::vec3 initial_pos);

    void receive_cursor_offset(float x_offset, float y_offset);
    void move(Player::Movement movement);

    void update(float delta_time);

    glm::mat4 get_view_matrix() const;

private:
    void update_vectors();

    glm::vec3 m_pos;
    glm::vec3 m_vel = glm::vec3(0.0f);
    glm::vec3 m_accel = glm::vec3(0.0f);
    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;

    float m_yaw = 90.0f;
    float m_pitch = 0.0f;
    bool m_key_just_held_bakersfield = false;
};

