#ifndef OPENWAY_VAO_HPP
#define OPENWAY_VAO_HPP


#include <glad/glad.h>

#include "openway/gl/descriptor.hpp"


OW_GL_DECLARE_DESCRIPTOR(
    VAO,
    glGenVertexArrays(1, *this),
    glDeleteVertexArrays(1, *this)
)

#endif // OPENWAY_VAO_HPP
