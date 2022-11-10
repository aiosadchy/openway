#ifndef OPENWAY_TO_STRING_HPP
#define OPENWAY_TO_STRING_HPP

#include <string>
#include <sstream>


template <typename... Ts>
std::string to_string(Ts &&...objects) {
    // TODO: a more efficient solution?
    std::ostringstream ss{};
    (ss << ... << objects);
    return ss.str();
}


#endif // OPENWAY_TO_STRING_HPP
