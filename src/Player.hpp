#pragma once

#include <array>

#include <glm/glm.hpp>

class Player {
public:
    enum Movement_direction {
        up = 0,
        down,
        left,
        right,
        forward,
        backward,
        num_directions
    };

    Player(glm::vec3 initial_pos);

    void process_movement(Movement_direction direction);
    void update(float delta_time);

    glm::mat4 get_view_matrix() const;

private:
    void update_vectors();

    std::array<bool, num_directions> m_movement;

    glm::vec3 m_pos;
    glm::vec3 m_vel = glm::vec3(0.0f);
    glm::vec3 m_accel = glm::vec3(0.0f);
    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;

    float m_yaw = 0.0f;
    float m_pitch = 0.0f;

};

