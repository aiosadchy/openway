#ifndef OPENWAY_INCLUDE_OPENWAY_GL_TEXTURE_HPP
#define OPENWAY_INCLUDE_OPENWAY_GL_TEXTURE_HPP

#include <glad/glad.h>
#include <utl/default_movable.hpp>

#include "openway/gl/call.hpp"
#include "openway/gl/gl_object.hpp"

class Texture : public GLObject<GLuint> {
public:
    Texture() {
        OW_GL_CALL(glGenTextures(1, get_handle_ptr()));
    }

    ~Texture() {
        if (*this) {
            OW_GL_CALL(glDeleteTextures(1, get_handle_ptr()));
        }
    }

    DEFAULT_MOVABLE(Texture)
};

#endif // OPENWAY_INCLUDE_OPENWAY_GL_TEXTURE_HPP
