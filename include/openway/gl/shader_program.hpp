#ifndef OPENWAY_INCLUDE_OPENWAY_GL_SHADER_PROGRAM_HPP
#define OPENWAY_INCLUDE_OPENWAY_GL_SHADER_PROGRAM_HPP

#include <stdexcept>
#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <utl/default_movable.hpp>

#include "openway/gl/gl_object.hpp"
#include "openway/gl/shader.hpp"
#include "openway/gl/uniform.hpp"

class ShaderProgram : public GLObject<GLuint> {
public:
    class LinkingError : public std::runtime_error {
    public:
        explicit LinkingError(GLuint descriptor);
        GLuint get_descriptor() const;

    private:
        GLuint m_descriptor;
    };

    ShaderProgram(Shader &&vertex, Shader &&fragment);
    ~ShaderProgram();

    DEFAULT_MOVABLE(ShaderProgram)

    void use() const;

    void set_uniform(const std::string &name, const Uniform &value);

    static ShaderProgram load_from_files(const std::string &vertex, const std::string &fragment);

private:
    GLint get_uniform_location(const std::string &name);

private:
    Shader m_vertex_shader;
    Shader m_fragment_shader;
    std::unordered_map<std::string, GLint> m_uniform_locations;
};


#endif // OPENWAY_INCLUDE_OPENWAY_GL_SHADER_PROGRAM_HPP
