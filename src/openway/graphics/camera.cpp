#include "openway/graphics/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(const glm::vec3 &position, const glm::vec2 &rotation)
    : m_position(position)
    , m_rotation(rotation) {
}

Camera::~Camera() = default;

const glm::vec3 &Camera::get_position() const {
    return m_position;
}

void Camera::set_position(const glm::vec3 &position) {
    m_position = position;
}

const glm::vec2 &Camera::get_rotation() const {
    return m_rotation;
}

void Camera::set_rotation(const glm::vec2 &rotation) {
    m_rotation = rotation;
}

void Camera::move(const glm::vec3 &offset) {
    m_position += offset;
}

void Camera::rotate(const glm::vec2 &amount) {
    const float max_yaw   = glm::pi<float>() * 2.0f;
    const float max_pitch = glm::pi<float>() * 0.5f;
    m_rotation += amount;
    m_rotation.x = glm::mod(m_rotation.x, max_yaw);
    m_rotation.y = glm::clamp(m_rotation.y, -max_pitch, max_pitch);
}

glm::mat4 Camera::get_projection_matrix() const {
    return glm::identity<glm::mat4>();
}

glm::mat4 Camera::get_view_matrix() const {
    glm::vec3 up {0.f, -1.f, 0.f};
    glm::vec3 left {-1.f, 0.f, 0.f};
    glm::mat4 camera = glm::identity<glm::mat4>();
    camera = glm::translate(camera, m_position);
    camera = glm::rotate(camera, m_rotation.x, up);
    camera = glm::rotate(camera, m_rotation.y, left);
    return glm::inverse(camera);
}

glm::mat3 Camera::get_directions() const {
    glm::mat4 directions = glm::identity<glm::mat4>();
    directions = glm::rotate(directions, m_rotation.x, {0.f, -1.f, 0.f});
    directions = glm::rotate(directions, m_rotation.y, {-1.f, 0.f, 0.f});
    return glm::mat3{directions};
}
