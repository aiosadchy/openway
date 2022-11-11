#ifndef OPENWAY_CALL_HPP
#define OPENWAY_CALL_HPP

#include <utility>

#include <glad/glad.h>

#include "openway/log.hpp"


namespace gl {

namespace detail {

class CommaGuard {
};

template <typename T>
T &&operator,(T &&t, CommaGuard) {
    return std::forward<T>(t);
}


template <typename TResult>
inline TResult wrap_call(TResult call_result, const char *file, int line) {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        // TODO: better output, support for debug callbacks, if constexpr
        Log::error(to_string("OpenGL error #", error), file, line);
    }
    return call_result;
}

inline void wrap_call(detail::CommaGuard, const char *file, int line) {
    wrap_call(0, file, line);
}

} // namespace detail

} // namespace gl


// TODO: do not wrap call into anything in release mode
#define OW_GL_CALL(call) gl::detail::wrap_call(((call), gl::detail::CommaGuard{}), __FILE__, __LINE__)

#endif // OPENWAY_CALL_HPP
