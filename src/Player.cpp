#include "Player.hpp"

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

constexpr glm::vec3 world_up(0.0f, 1.0f, 0.0f);

Player::Player(glm::vec3 initial_pos)
    : m_pos(initial_pos)
{
    update_vectors();
}

void Player::receive_cursor_offset(float x_offset, float y_offset)
{
    m_yaw += x_offset;
    m_pitch += y_offset;
}

void Player::move_forward()
{
    m_vel.z = 1.0;
}

void Player::update(float delta_time)
{
    m_pos += m_vel * delta_time;
    update_vectors();
}

glm::mat4 Player::get_view_matrix() const
{
    return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

void Player::update_vectors()
{
    glm::vec3 new_front(
            std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch)),
            std::sin(glm::radians(m_pitch)),
            std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch))
            );

    m_front = glm::normalize(new_front);
    m_right = glm::normalize(glm::cross(m_front, world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
