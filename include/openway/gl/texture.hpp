#ifndef OPENWAY_TEXTURE_HPP
#define OPENWAY_TEXTURE_HPP

#include <glad/glad.h>

#include "openway/gl/call.hpp"
#include "openway/gl/descriptor.hpp"


OW_GL_DECLARE_DESCRIPTOR(
    Texture,
    OW_GL_CALL(glGenTextures(1, *this)),
    OW_GL_CALL(glDeleteTextures(1, *this))
)

#endif // OPENWAY_TEXTURE_HPP
