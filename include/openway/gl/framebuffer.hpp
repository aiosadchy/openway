#ifndef OPENWAY_INCLUDE_OPENWAY_GL_FRAMEBUFFER_HPP
#define OPENWAY_INCLUDE_OPENWAY_GL_FRAMEBUFFER_HPP

#include <glad/glad.h>
#include <utl/default_movable.hpp>

#include "openway/gl/call.hpp"
#include "openway/gl/gl_object.hpp"

class Framebuffer : public GLObject<GLuint> {
public:
    Framebuffer() {
        OW_GL_CALL(glGenFramebuffers(1, get_descriptor_ptr()));
    }

    ~Framebuffer() {
        if (*this) {
            OW_GL_CALL(glDeleteFramebuffers(1, get_descriptor_ptr()));
        }
    }

    DEFAULT_MOVABLE(Framebuffer)
};

#endif // OPENWAY_INCLUDE_OPENWAY_GL_FRAMEBUFFER_HPP
