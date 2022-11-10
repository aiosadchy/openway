#ifndef OPENWAY_RENDERBUFFER_HPP
#define OPENWAY_RENDERBUFFER_HPP

#include <glad/glad.h>

#include "openway/gl/descriptor.hpp"


OW_GL_DECLARE_DESCRIPTOR(
    Renderbuffer,
    glGenRenderbuffers(1, *this),
    glDeleteRenderbuffers(1, *this)
)

#endif // OPENWAY_RENDERBUFFER_HPP
