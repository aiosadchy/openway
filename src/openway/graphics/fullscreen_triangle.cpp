#include "openway/graphics/fullscreen_triangle.hpp"

namespace {

constexpr GLfloat fullscreen_triangle_vertices[][3] = {
    {-1.0f, -1.0f, 0.0f},
    {+3.0f, -1.0f, 0.0f},
    {-1.0f, +3.0f, 0.0f},
};

} // namespace

FullscreenTriangle::FullscreenTriangle() {
    OW_GL_CALL(glBindVertexArray(m_vao));
    OW_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    OW_GL_CALL(glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(fullscreen_triangle_vertices),
        fullscreen_triangle_vertices,
        GL_STATIC_DRAW
    ));
    OW_GL_CALL(glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(GLfloat),
        NULL
    ));
    OW_GL_CALL(glEnableVertexAttribArray(0));
}

void FullscreenTriangle::draw() const {
    OW_GL_CALL(glBindVertexArray(m_vao));
    OW_GL_CALL(glDrawArrays(
        GL_TRIANGLES,
        0,
        std::size(fullscreen_triangle_vertices)
    ));
}
