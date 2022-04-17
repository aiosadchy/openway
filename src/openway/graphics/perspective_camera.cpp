#include "openway/graphics/perspective_camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


PerspectiveCamera::PerspectiveCamera(
        const glm::vec3 &position,
        const glm::vec2 &rotation,
        float fov,
        float aspect_ratio,
        float z_near,
        float z_far
)
    : Camera(position, rotation)
    , m_fov(fov)
    , m_aspect_ratio(aspect_ratio)
    , m_z_near(z_near)
    , m_z_far(z_far) {
}

PerspectiveCamera::~PerspectiveCamera() = default;

glm::mat4 PerspectiveCamera::get_projection_matrix() const {
    return glm::perspective(
        glm::radians(m_fov),
        m_aspect_ratio,
        m_z_near,
        m_z_far
    );
}
