#ifndef OPENWAY_INCLUDE_OPENWAY_GRAPHICS_RENDER_PASS_HPP
#define OPENWAY_INCLUDE_OPENWAY_GRAPHICS_RENDER_PASS_HPP

#include <cstddef>
#include <optional>
#include <vector>

#include <glad/glad.h>

#include "openway/gl/framebuffer.hpp"
#include "openway/gl/renderbuffer.hpp"
#include "openway/gl/texture.hpp"

class RenderPass {
public:
    RenderPass(
        std::size_t output_width,
        std::size_t output_height,
        std::vector<Texture::Reference> color_outputs,
        std::optional<Texture::Reference> depth_output = std::nullopt,
        bool use_stencil                               = false
    );

    void bind();

    const std::vector<Texture::Reference> &get_color_outputs() const;
    const std::optional<Texture::Reference> &get_depth_output() const;

private:
    void prepare_texture(Texture::Reference texture) const;
    void attach_color_output(Texture::Reference texture, GLenum index);
    void attach_depth_output(Texture::Reference texture, bool use_stencil);

private:
    std::size_t m_output_width;
    std::size_t m_output_height;
    std::vector<Texture::Reference> m_color_outputs;
    std::optional<Texture::Reference> m_depth_output;
    Framebuffer m_framebuffer;
    Renderbuffer m_renderbuffer;
};

#endif // OPENWAY_INCLUDE_OPENWAY_GRAPHICS_RENDER_PASS_HPP
