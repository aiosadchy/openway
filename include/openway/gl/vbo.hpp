#ifndef OPENWAY_INCLUDE_OPENWAY_GL_VBO_HPP
#define OPENWAY_INCLUDE_OPENWAY_GL_VBO_HPP

#include <glad/glad.h>
#include <utl/default_movable.hpp>

#include "openway/gl/call.hpp"
#include "openway/gl/gl_object.hpp"

class VBO : public GLObject<GLuint> {
public:
    VBO() {
        OW_GL_CALL(glGenBuffers(1, get_descriptor_ptr()));
    }

    ~VBO() {
        if (*this) {
            OW_GL_CALL(glDeleteBuffers(1, get_descriptor_ptr()));
        }
    }

    DEFAULT_MOVABLE(VBO)
};

#endif // OPENWAY_INCLUDE_OPENWAY_GL_VBO_HPP
