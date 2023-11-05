#ifndef OPENWAY_KEYBOARD_HPP
#define OPENWAY_KEYBOARD_HPP

#include <GLFW/glfw3.h>
#include <utl/non_copyable.hpp>

class Window;
struct InputState;

class Keyboard {
public:
    explicit Keyboard(Window &window);
    ~Keyboard();

    NON_COPYABLE(Keyboard)

    // TODO: better key identifiers
    bool is_pressed(int glfw_key) const;
    bool is_down(int glfw_key) const;
    bool is_released(int glfw_key) const;
    bool is_up(int glfw_key) const;

    void next_input_frame();

private:
    InputState *m_state_ptr;
};

#endif // OPENWAY_KEYBOARD_HPP
