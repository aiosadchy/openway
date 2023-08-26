#ifndef OPENWAY_INCLUDE_OPENWAY_GRAPHICS_MESH_HPP
#define OPENWAY_INCLUDE_OPENWAY_GRAPHICS_MESH_HPP

#include "openway/gl/vao.hpp"
#include "openway/gl/vbo.hpp"
#include "openway/graphics/drawable.hpp"

class Mesh : public Drawable {
public:
    // TODO: this is temporary
    Mesh(const std::string &obj_file);
    void draw() const override;

private:
    VAO m_vao;
    VBO m_vbo;
};

#endif // OPENWAY_INCLUDE_OPENWAY_GRAPHICS_MESH_HPP
