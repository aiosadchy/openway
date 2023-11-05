#ifndef OPENWAY_GLFW_SESSION_HPP
#define OPENWAY_GLFW_SESSION_HPP

#include <utl/non_copyable.hpp>


class GLFWSession {
public:
    GLFWSession();
    ~GLFWSession();

    NON_COPYABLE(GLFWSession)

private:
    static void error_callback(int error, const char* description);

};

#endif // OPENWAY_GLFW_SESSION_HPP
