#ifndef OPENWAY_INCLUDE_OPENWAY_GRAPHICS_FULLSCREEN_PASS_HPP
#define OPENWAY_INCLUDE_OPENWAY_GRAPHICS_FULLSCREEN_PASS_HPP

#include <cstddef>

#include <glad/glad.h>

#include "fullscreen_triangle.hpp"

#include "openway/gl/framebuffer.hpp"
#include "openway/gl/renderbuffer.hpp"
#include "openway/gl/shader_program.hpp"
#include "openway/gl/texture.hpp"

// TODO: change this class API as i don't like it much
class FullscreenPass {
public:
    FullscreenPass(
        std::size_t width,
        std::size_t height,
        GLint output_texture_format
    );

    // TODO: maybe move shader program to object properties
    void run();
    const Texture &get_output_texture() const;

private:
    std::size_t m_output_width;
    std::size_t m_output_height;
    Texture m_output_texture;
    Framebuffer m_framebuffer;
    Renderbuffer m_renderbuffer;
    FullscreenTriangle m_fullscreen_triangle;
};

#endif // OPENWAY_INCLUDE_OPENWAY_GRAPHICS_FULLSCREEN_PASS_HPP
