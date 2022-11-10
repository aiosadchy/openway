#ifndef OPENWAY_TEXTURE_HPP
#define OPENWAY_TEXTURE_HPP

#include <glad/glad.h>

#include "openway/gl/descriptor.hpp"


OW_GL_DECLARE_DESCRIPTOR(
    Texture,
    glGenTextures(1, *this),
    glDeleteTextures(1, *this)
)

#endif // OPENWAY_TEXTURE_HPP
