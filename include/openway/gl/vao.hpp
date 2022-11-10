#ifndef OPENWAY_VAO_HPP
#define OPENWAY_VAO_HPP


#include <glad/glad.h>

#include "openway/gl/descriptor.hpp"


using VAO = OW_GL_DECLARE_DESCRIPTOR(
    VAODescriptor,
    glGenVertexArrays(1, get_descriptor_address()),
    glDeleteVertexArrays(1, get_descriptor_address())
)

#endif // OPENWAY_VAO_HPP
