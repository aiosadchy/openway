#ifndef OPENWAY_INCLUDE_OPENWAY_GRAPHICS_FULLSCREEN_TRIANGLE_HPP
#define OPENWAY_INCLUDE_OPENWAY_GRAPHICS_FULLSCREEN_TRIANGLE_HPP

#include "openway/gl/vao.hpp"
#include "openway/gl/vbo.hpp"
#include "openway/graphics/drawable.hpp"

class FullscreenTriangle : public Drawable {
public:
    FullscreenTriangle();
    void draw() const override;

private:
    VAO m_vao;
    VBO m_vbo;
};

#endif // OPENWAY_INCLUDE_OPENWAY_GRAPHICS_FULLSCREEN_TRIANGLE_HPP
