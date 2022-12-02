#ifndef OPENWAY_INCLUDE_OPENWAY_GL_UNIFORM_HPP
#define OPENWAY_INCLUDE_OPENWAY_GL_UNIFORM_HPP

#include <variant>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace detail {

// TODO: add support for vector uniforms
using BaseUniform = std::variant<
    GLfloat,
    glm::vec1,
    glm::vec2,
    glm::vec3,
    glm::vec4,
    GLint,
    glm::ivec1,
    glm::ivec2,
    glm::ivec3,
    glm::ivec4,
    GLuint,
    glm::uvec1,
    glm::uvec2,
    glm::uvec3,
    glm::uvec4,
    glm::mat2,
    glm::mat3,
    glm::mat4,
    glm::mat2x3,
    glm::mat3x2,
    glm::mat2x4,
    glm::mat4x2,
    glm::mat3x4,
    glm::mat4x3>;

} // namespace detail

class Uniform : public detail::BaseUniform {
public:
    using detail::BaseUniform::BaseUniform;
};

#endif // OPENWAY_INCLUDE_OPENWAY_GL_UNIFORM_HPP
