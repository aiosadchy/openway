#ifndef OPENWAY_RENDERBUFFER_HPP
#define OPENWAY_RENDERBUFFER_HPP

#include <glad/glad.h>

#include "openway/gl/call.hpp"
#include "openway/gl/descriptor.hpp"


OW_GL_DECLARE_DESCRIPTOR(
    Renderbuffer,
    OW_GL_CALL(glGenRenderbuffers(1, *this)),
    OW_GL_CALL(glDeleteRenderbuffers(1, *this))
)

#endif // OPENWAY_RENDERBUFFER_HPP
