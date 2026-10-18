#pragma once

#include <array>

#include <glm/glm.hpp>

class Player {
public:
    Player(glm::vec3 initial_pos);

    void move_forward();
    
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

};

