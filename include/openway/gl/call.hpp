#ifndef OPENWAY_CALL_HPP
#define OPENWAY_CALL_HPP

#include <stdexcept>
#include <utility>

#include <glad/glad.h>

#include "openway/debug.hpp"
#include "openway/log.hpp"


namespace gl {

namespace detail {

class CommaGuard {
};

template <typename T>
inline T &&operator,(T &&t, CommaGuard) noexcept {
    return std::forward<T>(t);
}


inline const char *error_description(GLenum error_code) noexcept {
    switch (error_code) {
        case GL_NO_ERROR:                       return "no error";
        case GL_INVALID_ENUM:                   return "invalid enum";
        case GL_INVALID_VALUE:                  return "invalid value";
        case GL_INVALID_OPERATION:              return "invalid operation";
        case GL_INVALID_FRAMEBUFFER_OPERATION:  return "invalid framebuffer operation";
        case GL_OUT_OF_MEMORY:                  return "out of memory";
        case GL_STACK_UNDERFLOW:                return "stack underflow";
        case GL_STACK_OVERFLOW:                 return "stack overflow";
        default:                                return "unknown error";
    }
}

template <typename TResult>
inline TResult wrap_call(TResult call_result, const char *file, int line, bool throw_on_error = true) {
    bool error = false;
    GLenum error_code;
    while ((error_code = glGetError()) != GL_NO_ERROR) {
        error = true;
        // TODO: support for debug callbacks
        Log::error(
            to_string("OpenGL error #", error_code, ": ", error_description(error_code)),
            file,
            line
        );
    }
    if (error && throw_on_error) {
        Log::exception_logger(file, line) << std::runtime_error{"OpenGL error"};
    }
    return call_result;
}

inline void wrap_call(detail::CommaGuard, const char *file, int line, bool throw_on_error = true) {
    wrap_call(0, file, line, throw_on_error);
}

} // namespace detail

} // namespace gl


#ifdef OW_DEBUG
    #define OW_GL_CALL(call)                    \
        gl::detail::wrap_call(                  \
            ((call), gl::detail::CommaGuard{}), \
            __FILE__,                           \
            __LINE__,                           \
            true                                \
        )
#else
    #define OW_GL_CALL(call) call
#endif

#endif // OPENWAY_CALL_HPP
