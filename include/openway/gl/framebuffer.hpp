#ifndef OPENWAY_FRAMEBUFFER_HPP
#define OPENWAY_FRAMEBUFFER_HPP

#include <glad/glad.h>

#include "openway/gl/descriptor.hpp"


using Framebuffer = OW_GL_DECLARE_DESCRIPTOR(
    FramebufferDescriptor,
    glGenFramebuffers(1, get_descriptor_address()),
    glDeleteFramebuffers(1, get_descriptor_address())
)

#endif // OPENWAY_FRAMEBUFFER_HPP
