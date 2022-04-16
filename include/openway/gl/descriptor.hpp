#ifndef OPENWAY_DESCRIPTOR_HPP
#define OPENWAY_DESCRIPTOR_HPP

#include <algorithm>
#include <limits>

#include <glad/glad.h>
#include <utl/non_copyable.hpp>


template <
    typename TUnderlyingType,
    TUnderlyingType V_DEFAULT_VALUE = std::numeric_limits<TUnderlyingType>::max()
>
class Descriptor {
public:
    using UnderlyingType = TUnderlyingType;
    static constexpr UnderlyingType DEFAULT_VALUE = V_DEFAULT_VALUE;

    NON_COPYABLE(Descriptor)

    Descriptor(Descriptor &&another) noexcept {
        m_value = another.m_value;
        another.m_value = std::numeric_limits<UnderlyingType>::max();
    }

    Descriptor &operator=(Descriptor &&another) noexcept {
        std::swap(m_value, another.m_value);
        return *this;
    }

    operator UnderlyingType() const {
        return m_value;
    }

    bool is_initialized() const {
        return m_value != DEFAULT_VALUE;
    }

protected:
    explicit Descriptor(UnderlyingType value = DEFAULT_VALUE)
        : m_value(value) {
    }

    ~Descriptor() = default;

    UnderlyingType *get_descriptor_address() {
        return &m_value;
    }

private:
    UnderlyingType m_value;

};

#endif // OPENWAY_DESCRIPTOR_HPP
