#include "openway/graphics/orthographic_camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


OrthographicCamera::OrthographicCamera(
        const glm::vec3 &position,
        const glm::vec2 &rotation,
        const glm::vec2 &size,
        float z_near,
        float z_far
)
    : Camera(position, rotation)
    , m_size(size)
    , m_z_near(z_near)
    , m_z_far(z_far) {
}

OrthographicCamera::~OrthographicCamera() = default;

glm::mat4 OrthographicCamera::get_projection_matrix() const {
    const glm::vec2 half_size = 0.5f * m_size;
    return glm::ortho(
        -half_size.x,
        +half_size.x,
        -half_size.y,
        +half_size.y,
        m_z_near,
        m_z_far
    );
}
