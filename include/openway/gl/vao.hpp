#ifndef OPENWAY_VAO_HPP
#define OPENWAY_VAO_HPP


#include <glad/glad.h>

#include "openway/gl/call.hpp"
#include "openway/gl/descriptor.hpp"


OW_GL_DECLARE_DESCRIPTOR(
    VAO,
    OW_GL_CALL(glGenVertexArrays(1, *this)),
    OW_GL_CALL(glDeleteVertexArrays(1, *this))
)

#endif // OPENWAY_VAO_HPP
