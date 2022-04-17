#include <iostream>

#include <utl/utl.hpp>

#include "openway/gl/framebuffer.hpp"
#include "openway/gl/renderbuffer.hpp"
#include "openway/gl/texture.hpp"
#include "openway/gl/vao.hpp"
#include "openway/gl/vbo.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv) {
    Texture texture;
    UTL_REPEAT(1) {
        std::cout << "Everything seems to be working..." << std::endl;
    }
    return 0;
}
