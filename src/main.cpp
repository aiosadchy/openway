#include <iostream>

#include <utl/utl.hpp>

#include "openway/gl/framebuffer.hpp"
#include "openway/gl/glad_session.hpp"
#include "openway/gl/glfw_session.hpp"
#include "openway/gl/renderbuffer.hpp"
#include "openway/gl/shader_program.hpp"
#include "openway/gl/texture.hpp"
#include "openway/gl/vao.hpp"
#include "openway/gl/vbo.hpp"
#include "openway/io/window.hpp"
#include "openway/utility/debug.hpp"
#include "openway/utility/log.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv) {
    GLFWSession glfw_session{};

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    // glfwWindowHint(GLFW_DECORATED,              GLFW_FALSE);
    glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);


    Window window{800, 600, "Openway", nullptr};
    glfwMakeContextCurrent(window);

    GLADSession glad_session{};

    [[maybe_unused]] Uniform x = glm::vec2{1, 2};

    Framebuffer framebuffer;
    Renderbuffer renderbuffer;
    Texture texture;
    VAO vao;
    VBO vbo;
    UTL_REPEAT(1) {
        std::cout << "Everything seems to be working..." << std::endl;
    }

    try {
        try {
            OW_LOG_THROW std::runtime_error{"a regular exception"};
        } catch (const std::runtime_error &e) {
            OW_LOG_THROW std::runtime_error{"another error"};
        }
    } catch (const std::exception &e) {
        auto messages = unwrap_exception(e);
        for (const std::string &message : messages) {
            std::cout << " - " << message << std::endl;
        }
    }

    try {
        OW_GL_CALL(glBindTexture(GL_VERTEX_SHADER, texture));
    } catch (...) {
    }

    std::cout << OW_SOURCE_ROOT << std::endl;
    std::cout << __FILE__ << std::endl;

    OW_LOG_DEBUG("debug message ", 12, " ", argc, argv[0]);

    OW_DEBUG_SECTION(
        std::cout << "!!!!! debug section!" << std::endl;
    )

    bool is_running = true;

    while (is_running) {
        glfwSwapBuffers(window);

        glfwPollEvents();

        if (glfwWindowShouldClose(window)) {
            is_running = false;
        }
    }

    return 0;
}
