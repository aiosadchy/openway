#include "openway/gl/glfw_session.hpp"

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

GLFWSession::GLFWSession() {
    if (!glfwInit()) {
        throw std::runtime_error("error creating GLFW session");
    }
    glfwSetErrorCallback(error_callback);
}

GLFWSession::~GLFWSession() {
    glfwTerminate();
}

void GLFWSession::error_callback(int error, const char *description) {
    // TODO: proper logging
    std::cerr << "GLFW error [" << error << "]: " << description << std::endl;
}
