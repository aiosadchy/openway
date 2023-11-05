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
#include "openway/graphics/fullscreen_triangle.hpp"
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

    glEnable(GL_CULL_FACE);

    bool is_running = true;

    ShaderProgram shader_program = ShaderProgram::load_from_files(
        "data/shaders/fullscreen.vert",
        "data/shaders/fullscreen.frag"
    );
    shader_program.use();

    FullscreenTriangle fullscreen_triangle;

    while (is_running) {
        glfwPollEvents();

        fullscreen_triangle.draw();

        if (glfwWindowShouldClose(window)) {
            is_running = false;
        }

        glfwSwapBuffers(window);
    }

    return 0;
}
