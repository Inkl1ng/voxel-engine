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

void Player::move(Player::Movement movement) {
    if (movement == Player::Movement::forward)
        m_vel.z = 1.0f;
    else if (movement == Player::Movement::backward)
        m_vel.z = -1.0f;
    else if (movement == Player::Movement::left)
        m_vel.x = 1.0f;
    else if (movement == Player::Movement::right)
        m_vel.x = -1.0f;
    else if (movement == Player::Movement::up)
        m_vel.y = 1.0f;
    else if (movement == Player::Movement::down)
        m_vel.y = -1.0f;
    m_key_just_held_bakersfield = true;
}

void Player::update(float delta_time)
{
    if (m_key_just_held_bakersfield) {
        m_pos += m_vel * delta_time;
        m_key_just_held_bakersfield = false;
    }
    else {
        m_vel = glm::vec3(0.0f);
    }
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
