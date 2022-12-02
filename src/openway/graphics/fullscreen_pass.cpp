#include "openway/graphics/fullscreen_pass.hpp"

#include <iterator>
#include <stdexcept>

#include "openway/utility/log.hpp"

FullscreenPass::FullscreenPass(
    std::size_t width,
    std::size_t height,
    GLint output_texture_format
)
: m_output_width{width}
, m_output_height{height} {
    OW_GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer));
    OW_GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer));

    OW_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_output_texture));
    OW_GL_CALL(glTexImage2D(
        GL_TEXTURE_2D,         // target,
        0,                     // level,
        output_texture_format, // internal format,
        width,                 // width,
        height,                // height,
        0,                     // border,
        GL_RGB,                // format,
        GL_UNSIGNED_BYTE,      // type,
        NULL                   // data
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

    OW_GL_CALL(glFramebufferTexture(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        m_output_texture,
        0 // level
    ));

    // TODO: add support for multiple outputs
    GLenum draw_buffers[1] = {GL_COLOR_ATTACHMENT0};
    OW_GL_CALL(glDrawBuffers(std::size(draw_buffers), draw_buffers));

    GLenum status = OW_GL_CALL(glCheckFramebufferStatus(GL_FRAMEBUFFER));
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        OW_LOG_THROW std::runtime_error{"framebuffer is incomplete"};
    }
}

void FullscreenPass::run() {
    OW_GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer));
    OW_GL_CALL(glViewport(0, 0, m_output_width, m_output_height));
    // TODO: implementation
}

const Texture &FullscreenPass::get_output_texture() const {
    return m_output_texture;
}
