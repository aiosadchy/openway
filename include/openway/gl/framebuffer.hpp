#ifndef OPENWAY_FRAMEBUFFER_HPP
#define OPENWAY_FRAMEBUFFER_HPP

#include <glad/glad.h>

#include "openway/gl/descriptor.hpp"


OW_GL_DECLARE_DESCRIPTOR(
    Framebuffer,
    glGenFramebuffers(1, *this),
    glDeleteFramebuffers(1, *this)
)

#endif // OPENWAY_FRAMEBUFFER_HPP
