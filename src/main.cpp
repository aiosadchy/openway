#include <iostream>

#include <utl/utl.hpp>

#include "openway/io/window.hpp"
#include "openway/gl/glad_session.hpp"
#include "openway/gl/glfw_session.hpp"
#include "openway/gl/framebuffer.hpp"
#include "openway/gl/renderbuffer.hpp"
#include "openway/gl/texture.hpp"
#include "openway/gl/vao.hpp"
#include "openway/gl/vbo.hpp"

#include "openway/log.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv) {
    GLFWSession glfw_session{};
    Window window{800, 600, "Openway", nullptr};
    glfwMakeContextCurrent(window);
    GLADSession glad_session{};
    Framebuffer framebuffer;
    Renderbuffer renderbuffer;
    Texture texture;
    VAO vao;
    VBO vbo;
    UTL_REPEAT(1) {
        std::cout << "Everything seems to be working..." << std::endl;
    }

    try {
        OW_LOG_THROW std::runtime_error("a regular exception occurred!");
    } catch (const std::runtime_error &e) {
        OW_LOG_INFO("caught exception: ", e.what());
    }

    std::cout << OPENWAY_SOURCE_ROOT << std::endl;
    std::cout << __FILE__ << std::endl;

    OW_LOG_DEBUG("asdasda ", 12, " ", argc, argv[0]);

    return 0;
}
