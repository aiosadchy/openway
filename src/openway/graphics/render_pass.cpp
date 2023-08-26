#include "openway/graphics/render_pass.hpp"

#include <stdexcept>
#include <vector>

#include "openway/utility/log.hpp"

RenderPass::RenderPass(
    std::size_t output_width,
    std::size_t output_height,
    std::vector<Texture::Descriptor> color_outputs,
    std::optional<Texture::Descriptor> depth_output,
    bool use_stencil
)
: m_output_width{output_width}
, m_output_height{output_height}
, m_color_outputs{std::move(color_outputs)}
, m_depth_output{std::move(depth_output)} {
    OW_GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer));
    OW_GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer));

    std::vector<GLenum> draw_buffers = {};
    for (Texture::Descriptor texture : m_color_outputs) {
        draw_buffers.emplace_back(GL_COLOR_ATTACHMENT0 + draw_buffers.size());
        attach_color_output(texture, draw_buffers.back());
    }

    if (m_depth_output.has_value()) {
        attach_depth_output(m_depth_output.value(), use_stencil);
    }

    OW_GL_CALL(glDrawBuffers(draw_buffers.size(), draw_buffers.data()));

    GLenum status = OW_GL_CALL(glCheckFramebufferStatus(GL_FRAMEBUFFER));
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        OW_LOG_THROW std::runtime_error{"framebuffer is incomplete"};
    }
}

void RenderPass::bind() {
    OW_GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer));
    OW_GL_CALL(glViewport(0, 0, m_output_width, m_output_height));
}

const std::vector<Texture::Descriptor> &RenderPass::get_color_outputs() const {
    return m_color_outputs;
}

const std::optional<Texture::Descriptor> &RenderPass::get_depth_output() const {
    return m_depth_output;
}

void RenderPass::attach_color_output(Texture::Descriptor texture, GLenum index) {
    OW_GL_CALL(glFramebufferTexture(
        GL_FRAMEBUFFER,
        index,
        texture,
        0 // level
    ));
}

void RenderPass::attach_depth_output(
    Texture::Descriptor texture,
    bool use_stencil
) {
    GLenum attachment_type = GL_DEPTH_ATTACHMENT;
    if (use_stencil) {
        attachment_type = GL_DEPTH_STENCIL_ATTACHMENT;
    }
    OW_GL_CALL(glFramebufferTexture(
        GL_FRAMEBUFFER,
        attachment_type,
        texture,
        0 // level
    ));
}

void RenderPass::prepare_texture(Texture::Descriptor texture) const {
    // TODO: add support for internal texture formats
    OW_GL_CALL(glBindTexture(GL_TEXTURE_2D, texture));
    OW_GL_CALL(glTexImage2D(
        GL_TEXTURE_2D,    // target,
        0,                // level,
        GL_RGB8,          // internal format,
        m_output_width,   // width,
        m_output_height,  // height,
        0,                // border,
        GL_RGB,           // format,
        GL_UNSIGNED_BYTE, // type,
        NULL              // data
    ));
    OW_GL_CALL(glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_NEAREST
    ));
    OW_GL_CALL(glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_NEAREST
    ));
}
