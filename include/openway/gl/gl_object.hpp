#ifndef OPENWAY_INCLUDE_OPENWAY_GL_GL_OBJECT_HPP
#define OPENWAY_INCLUDE_OPENWAY_GL_GL_OBJECT_HPP

#include <limits>
#include <utility>

#include <glad/glad.h>
#include <utl/non_copyable.hpp>

template <
    typename TDescriptor,
    TDescriptor V_NULL_VALUE = std::numeric_limits<TDescriptor>::max()>
class GLObject {
public:
    using Descriptor                       = TDescriptor;
    static constexpr Descriptor NULL_VALUE = V_NULL_VALUE;

public:
    class Reference {
    public:
        Reference(const GLObject &object)
        : m_handle{object} {
        }

        operator Descriptor() const {
            return m_handle;
        }

        operator bool() const {
            return m_handle != NULL_VALUE;
        }

    private:
        Descriptor m_handle;
    };

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

    operator Descriptor() const {
        return m_handle;
    }

    operator bool() const {
        return m_handle != NULL_VALUE;
    }

protected:
    explicit GLObject(Descriptor handle = NULL_VALUE)
    : m_handle{handle} {
    }

    ~GLObject() = default;

    Descriptor *get_descriptor_ptr() {
        return &m_handle;
    }

private:
    Descriptor m_handle;
};

#endif // OPENWAY_INCLUDE_OPENWAY_GL_GL_OBJECT_HPP
