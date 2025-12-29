#pragma once

#include <glm/glm.hpp>

class Player {
public:
    Player();
    Player(glm::vec3 initial_pos = glm::vec3(0.0f, 0.0f, 0.0f));

    glm::mat4 get_view_matrix() const;

private:
    void update_vectors();

    glm::vec3 m_pos;
    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;

    float m_yaw = 0.0f;
    float m_pitch = 0.0f;

};

