#include "openway/io/window.hpp"

#include <stdexcept>

#include "openway/io/input_state.hpp"
#include "openway/log.hpp"

Window::Window(
    int width,
    int height,
    const std::string &title,
    GLFWmonitor *monitor
)
: m_handle{glfwCreateWindow(width, height, title.c_str(), monitor, nullptr)}
, m_state_ptr{std::make_unique<InputState>()} {
    if (m_handle == nullptr) {
        OW_LOG_THROW std::runtime_error{"error creating GLFW-managed window"};
    }
    glfwSetWindowUserPointer(m_handle, this);
    m_keyboard_ptr = std::make_unique<Keyboard>(*this);
    m_mouse_ptr    = std::make_unique<Mouse>(*this);
}

Window::~Window() {
    if (m_handle != nullptr) {
        glfwDestroyWindow(m_handle);
    }
}

Window::operator GLFWwindow *() {
    return m_handle;
}

Window::operator const GLFWwindow *() const {
    return m_handle;
}

void Window::next_input_frame() {
    m_keyboard_ptr->next_input_frame();
    m_mouse_ptr->next_input_frame();
}

const Keyboard &Window::get_keyboard() const {
    return *m_keyboard_ptr;
}

const Mouse &Window::get_mouse() const {
    return *m_mouse_ptr;
}
