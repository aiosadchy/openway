#ifndef OPENWAY_RENDERBUFFER_HPP
#define OPENWAY_RENDERBUFFER_HPP

#include <glad/glad.h>

#include "openway/gl/descriptor.hpp"


using Renderbuffer = OW_GL_DECLARE_DESCRIPTOR(
    RenderbufferDescriptor,
    glGenRenderbuffers(1, get_descriptor_address()),
    glDeleteRenderbuffers(1, get_descriptor_address())
)

#endif // OPENWAY_RENDERBUFFER_HPP
