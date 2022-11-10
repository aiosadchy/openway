#ifndef OPENWAY_VBO_HPP
#define OPENWAY_VBO_HPP


#include <glad/glad.h>

#include "openway/gl/descriptor.hpp"


using VBO = OW_GL_DECLARE_DESCRIPTOR(
    VBODescriptor,
    glGenBuffers(1, get_descriptor_address()),
    glDeleteBuffers(1, get_descriptor_address())
)

#endif // OPENWAY_VBO_HPP
