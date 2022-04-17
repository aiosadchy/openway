#ifndef OPENWAY_CAMERA_HPP
#define OPENWAY_CAMERA_HPP

#include <glm/glm.hpp>


class Camera {
public:
    Camera(const glm::vec3 &position, const glm::vec2 &rotation);
    ~Camera();

    const glm::vec3 &get_position() const;
    void set_position(const glm::vec3 &position);
    const glm::vec2 &get_rotation() const;
    void set_rotation(const glm::vec2 &rotation);

    void move(const glm::vec3 &offset);
    void rotate(const glm::vec2 &amount);

    virtual glm::mat4 get_projection_matrix() const;
    glm::mat4 get_view_matrix() const;
    glm::mat3 get_directions() const;

private:
    glm::vec3 m_position;
    glm::vec2 m_rotation;

};

#endif // OPENWAY_CAMERA_HPP
