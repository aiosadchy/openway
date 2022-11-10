#include "openway/gl/glfw_session.hpp"

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>


namespace {

// TODO: make this thread-safe?
bool s_glfw_session_is_initialized = false;

} // namespace


GLFWSession::GLFWSession() {
    if (s_glfw_session_is_initialized) {
        throw std::runtime_error("glfw is already initialized");
    }
    if (!glfwInit()) {
        throw std::runtime_error("error creating GLFW session");
    }
    s_glfw_session_is_initialized = true;
    glfwSetErrorCallback(error_callback);
}

GLFWSession::~GLFWSession() {
    glfwTerminate();
}

void GLFWSession::error_callback(int error, const char *description) {
    // TODO: proper logging
    std::cerr << "GLFW error [" << error << "]: " << description << std::endl;
}
