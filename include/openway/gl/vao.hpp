#ifndef OPENWAY_INCLUDE_OPENWAY_GL_VAO_HPP
#define OPENWAY_INCLUDE_OPENWAY_GL_VAO_HPP

#include <glad/glad.h>
#include <utl/default_movable.hpp>

#include "openway/gl/call.hpp"
#include "openway/gl/gl_object.hpp"

class VAO : public GLObject<GLuint> {
public:
    VAO() {
        OW_GL_CALL(glGenVertexArrays(1, get_descriptor_ptr()));
    }

    ~VAO() {
        if (*this) {
            OW_GL_CALL(glDeleteVertexArrays(1, get_descriptor_ptr()));
        }
    }

    DEFAULT_MOVABLE(VAO)
};

#endif // OPENWAY_INCLUDE_OPENWAY_GL_VAO_HPP
