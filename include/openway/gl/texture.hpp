#ifndef OPENWAY_TEXTURE_HPP
#define OPENWAY_TEXTURE_HPP

#include <glad/glad.h>

#include "openway/gl/descriptor.hpp"


OW_GL_DESCRIPTOR(
    Texture,
    GLuint,
    glGenTextures(1, get_descriptor_address()),
    glDeleteTextures(1, get_descriptor_address())
)

#endif // OPENWAY_TEXTURE_HPP
