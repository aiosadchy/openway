#ifndef OPENWAY_KEYBOARD_HPP
#define OPENWAY_KEYBOARD_HPP

#include <memory>

#include <GLFW/glfw3.h>
#include <utl/non_copyable.hpp>

#include "openway/io/input_state.hpp"

class Keyboard {
public:
    explicit Keyboard(
        GLFWwindow *window_handle,
        std::shared_ptr<InputState> input_state
    );
    ~Keyboard();

    NON_COPYABLE(Keyboard)

    // TODO: better key identifiers
    bool is_pressed(int glfw_key) const;
    bool is_down(int glfw_key) const;
    bool is_released(int glfw_key) const;
    bool is_up(int glfw_key) const;

    void next_input_frame();

private:
    std::shared_ptr<InputState> m_state_ptr;
};

#endif // OPENWAY_KEYBOARD_HPP
