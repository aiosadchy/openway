#ifndef OPENWAY_KEYBOARD_HPP
#define OPENWAY_KEYBOARD_HPP

#include <GLFW/glfw3.h>

#include "openway/io/window.hpp"


class Keyboard {
public:
    explicit Keyboard(Window &window);
    ~Keyboard();

    // TODO: better key identifiers
    bool is_pressed(int key) const;
    bool is_down(int key) const;
    bool is_released(int key) const;
    bool is_up(int key) const;

    void tick();

    static void initialize_keyboard(Window &window);

private:
    GLFWwindow *m_window_handle;

};

#endif // OPENWAY_KEYBOARD_HPP
