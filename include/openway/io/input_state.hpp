#ifndef OPENWAY_INCLUDE_OPENWAY_IO_INPUT_STATE_HPP
#define OPENWAY_INCLUDE_OPENWAY_IO_INPUT_STATE_HPP

#include <array>

#include <GLFW/glfw3.h>

struct InputState {
public:
    using Keyboard = std::array<std::array<bool, 4>, GLFW_KEY_LAST + 1>;

    struct Mouse {
    public:
        struct Position {
            double x = 0.0f;
            double y = 0.0f;
        };

    public:
        Position current_position  = {};
        Position previous_position = {};
    };

public:
    Keyboard keyboard = {};
    Mouse mouse       = {};
};

#endif // OPENWAY_INCLUDE_OPENWAY_IO_INPUT_STATE_HPP
