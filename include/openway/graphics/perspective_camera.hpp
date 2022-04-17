#ifndef OPENWAY_PERSPECTIVE_CAMERA_HPP
#define OPENWAY_PERSPECTIVE_CAMERA_HPP

#include "openway/graphics/camera.hpp"


class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(
            const glm::vec3 &position,
            const glm::vec2 &rotation,
            float fov,
            float aspect_ratio,
            float z_near,
            float z_far
    );

    ~PerspectiveCamera();

    glm::mat4 get_projection_matrix() const override;

private:
    glm::vec3 m_position;
    glm::vec2 m_rotation;
    float m_fov;
    float m_aspect_ratio;
    float m_z_near;
    float m_z_far;

};

#endif // OPENWAY_PERSPECTIVE_CAMERA_HPP
