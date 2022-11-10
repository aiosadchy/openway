#ifndef OPENWAY_VBO_HPP
#define OPENWAY_VBO_HPP


#include <glad/glad.h>

#include "openway/gl/descriptor.hpp"


OW_GL_DECLARE_DESCRIPTOR(
    VBO,
    glGenBuffers(1, *this),
    glDeleteBuffers(1, *this)
)

#endif // OPENWAY_VBO_HPP
