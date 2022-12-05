#ifndef OPENWAY_INCLUDE_OPENWAY_GL_GL_OBJECT_HPP
#define OPENWAY_INCLUDE_OPENWAY_GL_GL_OBJECT_HPP

#include <limits>
#include <utility>

#include <glad/glad.h>
#include <utl/non_copyable.hpp>

template <
    typename THandle,
    THandle V_NULL_VALUE = std::numeric_limits<THandle>::max()>
class GLObject {
public:
    using Handle                       = THandle;
    static constexpr Handle NULL_VALUE = V_NULL_VALUE;

public:
    NON_COPYABLE(GLObject)

    GLObject(GLObject &&another) noexcept
    : GLObject{NULL_VALUE} {
        *this = std::move(another);
    }

    GLObject &operator=(GLObject &&another) noexcept {
        std::swap(m_handle, another.m_handle);
        return *this;
    }

    operator Handle() const {
        return m_handle;
    }

    operator bool() const {
        return m_handle != NULL_VALUE;
    }

protected:
    explicit GLObject(Handle handle = NULL_VALUE)
    : m_handle{handle} {
    }

    ~GLObject() = default;

    Handle *get_handle_ptr() {
        return &m_handle;
    }

private:
    Handle m_handle;
};

#endif // OPENWAY_INCLUDE_OPENWAY_GL_GL_OBJECT_HPP
