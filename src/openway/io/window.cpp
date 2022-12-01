#include "openway/io/window.hpp"

#include <stdexcept>

#include "openway/log.hpp"

Window::Window(int width, int height, const std::string &title, GLFWmonitor *monitor)
    : m_handle{glfwCreateWindow(width, height, title.c_str(), monitor, nullptr)}
    , m_state_ptr{std::make_shared<InputState>(m_handle)}
    , m_keyboard_ptr{std::make_unique<Keyboard>(m_handle, m_state_ptr)}
    , m_mouse_ptr{std::make_unique<Mouse>(m_handle, m_state_ptr)} {
    if (m_handle == nullptr) {
        OW_LOG_THROW std::runtime_error{"error creating window"};
    }
    glfwSetWindowUserPointer(m_handle, this);
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
