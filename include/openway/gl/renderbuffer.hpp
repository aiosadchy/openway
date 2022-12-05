#ifndef OPENWAY_INCLUDE_OPENWAY_GL_RENDERBUFFER_HPP
#define OPENWAY_INCLUDE_OPENWAY_GL_RENDERBUFFER_HPP

#include <glad/glad.h>
#include <utl/default_movable.hpp>

#include "openway/gl/call.hpp"
#include "openway/gl/gl_object.hpp"

class Renderbuffer : public GLObject<GLuint> {
public:
    Renderbuffer() {
        OW_GL_CALL(glGenRenderbuffers(1, get_handle_ptr()));
    }

    ~Renderbuffer() {
        if (*this) {
            OW_GL_CALL(glDeleteRenderbuffers(1, get_handle_ptr()));
        }
    }

    DEFAULT_MOVABLE(Renderbuffer)
};

#endif // OPENWAY_INCLUDE_OPENWAY_GL_RENDERBUFFER_HPP
