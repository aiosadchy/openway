#ifndef OPENWAY_WINDOW_HPP
#define OPENWAY_WINDOW_HPP

#include <memory>
#include <string>

#include <GLFW/glfw3.h>
#include <utl/non_copyable.hpp>

#include "openway/io/keyboard.hpp"
#include "openway/io/mouse.hpp"

struct InputState;

class Window {
public:
    Window(int width, int height, const std::string &title, GLFWmonitor *monitor);
    ~Window();

    NON_COPYABLE(Window)

    void next_input_frame();

    const Keyboard &get_keyboard() const;
    const Mouse &get_mouse() const;

    operator GLFWwindow *();
    operator const GLFWwindow *() const;

private:
    GLFWwindow *m_handle;
    std::unique_ptr<InputState> m_state_ptr;
    std::unique_ptr<Keyboard> m_keyboard_ptr;
    std::unique_ptr<Mouse> m_mouse_ptr;
};

#endif // OPENWAY_WINDOW_HPP
