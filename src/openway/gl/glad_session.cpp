#include "openway/gl/glad_session.hpp"

#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace {

// TODO: make this thread-safe?
bool s_glad_session_is_initialized = false;

} // namespace


GLADSession::GLADSession() {
    if (s_glad_session_is_initialized) {
        throw std::runtime_error("glad session is already initialized");
    }
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("error loading OpenGL");
    }
    s_glad_session_is_initialized = true;
}

GLADSession::~GLADSession() {
    s_glad_session_is_initialized = false;
}
