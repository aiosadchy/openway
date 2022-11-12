#include "openway/gl/glfw_session.hpp"

#include <stdexcept>

#include <GLFW/glfw3.h>

#include "openway/log.hpp"


namespace {

// TODO: make this thread-safe?
bool s_glfw_session_is_initialized = false;

} // namespace


GLFWSession::GLFWSession() {
    if (s_glfw_session_is_initialized) {
        OW_LOG_THROW std::runtime_error{"GLFW is already initialized"};
    }
    if (!glfwInit()) {
        OW_LOG_THROW std::runtime_error{"error creating GLFW session"};
    }
    s_glfw_session_is_initialized = true;
    glfwSetErrorCallback(error_callback);
}

GLFWSession::~GLFWSession() {
    glfwTerminate();
}

void GLFWSession::error_callback(int error, const char *description) {
    OW_LOG_ERROR("GLFW error #" , error , ": ", description);
}
