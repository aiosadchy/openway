#ifndef OPENWAY_DEBUG_HPP
#define OPENWAY_DEBUG_HPP

#include <exception>
#include <string>
#include <vector>


#ifdef OW_DEBUG
    #define OW_DEBUG_SECTION(...) __VA_ARGS__
#else
    #define OW_DEBUG_SECTION(...)
#endif


constexpr bool is_debug() noexcept {
    #ifdef OW_DEBUG
        return true;
    #else
        return false;
    #endif
}

std::vector<std::string> unwrap_exception(const std::exception &exception) noexcept;

#endif // OPENWAY_DEBUG_HPP
