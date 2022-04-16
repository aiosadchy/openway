#include "openway/gl/glad_session.hpp"

#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


GLADSession::GLADSession() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("error loading OpenGL");
    }
}

GLADSession::~GLADSession() = default;
