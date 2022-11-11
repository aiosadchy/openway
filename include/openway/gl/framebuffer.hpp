#ifndef OPENWAY_FRAMEBUFFER_HPP
#define OPENWAY_FRAMEBUFFER_HPP

#include <glad/glad.h>

#include "openway/gl/call.hpp"
#include "openway/gl/descriptor.hpp"


OW_GL_DECLARE_DESCRIPTOR(
    Framebuffer,
    OW_GL_CALL(glGenFramebuffers(1, *this)),
    OW_GL_CALL(glDeleteFramebuffers(1, *this))
)

#endif // OPENWAY_FRAMEBUFFER_HPP
