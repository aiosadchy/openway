#include "openway/io/window.hpp"

#include <stdexcept>

#include "openway/log.hpp"


Window::Window(int width, int height, const std::string &title, GLFWmonitor *monitor)
    : m_handle(glfwCreateWindow(width, height, title.c_str(), monitor, nullptr)) {
    if (m_handle == nullptr) {
        OW_LOG_THROW std::runtime_error("error creating window");
    }
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
