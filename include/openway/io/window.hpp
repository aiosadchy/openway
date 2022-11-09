#ifndef OPENWAY_WINDOW_HPP
#define OPENWAY_WINDOW_HPP

#include <string>

#include <GLFW/glfw3.h>
#include <utl/non_copyable.hpp>


class Window {
public:
    Window(int width, int height, const std::string &title, GLFWmonitor *monitor);
    ~Window();

    NON_COPYABLE(Window)

    operator GLFWwindow *();
    operator const GLFWwindow *() const;

private:
    GLFWwindow* m_handle;

};

#endif // OPENWAY_WINDOW_HPP
