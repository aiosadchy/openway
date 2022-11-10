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
    Texture texture;
    UTL_REPEAT(1) {
        std::cout << "Everything seems to be working..." << std::endl;
    }

    std::cout << OPENWAY_SOURCE_ROOT << std::endl;
    std::cout << __FILE__ << std::endl;

    OW_LOG_DEBUG("asdasda ", 12, " ", argc, argv[0]);

    return 0;
}
