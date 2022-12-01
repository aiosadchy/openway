#ifndef OPENWAY_VBO_HPP
#define OPENWAY_VBO_HPP


#include <glad/glad.h>

#include "openway/gl/call.hpp"
#include "openway/gl/descriptor.hpp"


OW_GL_DECLARE_DESCRIPTOR(
    VBO,
    OW_GL_CALL(glGenBuffers(1, *this)),
    OW_GL_CALL(glDeleteBuffers(1, *this))
)

#endif // OPENWAY_VBO_HPP
