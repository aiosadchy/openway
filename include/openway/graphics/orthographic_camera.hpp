#ifndef OPENWAY_ORTHOGRAPHIC_CAMERA_HPP
#define OPENWAY_ORTHOGRAPHIC_CAMERA_HPP

#include "openway/graphics/camera.hpp"


class OrthographicCamera : public Camera {
public:
    OrthographicCamera(
            const glm::vec3 &position,
            const glm::vec2 &rotation,
            const glm::vec2 &size,
            float z_near,
            float z_far
    );

    ~OrthographicCamera();

    glm::mat4 get_projection_matrix() const override;

private:
    glm::vec2 m_size;
    float m_z_near;
    float m_z_far;

};

#endif // OPENWAY_ORTHOGRAPHIC_CAMERA_HPP
