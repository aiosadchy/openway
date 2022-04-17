#ifndef OPENWAY_SHADER_PROGRAM_HPP
#define OPENWAY_SHADER_PROGRAM_HPP

#include <stdexcept>
#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <utl/default_movable.hpp>
#include <utl/non_copyable.hpp>

#include "openway/gl/descriptor.hpp"
#include "openway/gl/shader.hpp"


class ShaderProgram : public Descriptor<GLuint> {
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

    void use();
    // TODO: more overloads
    void set_uniform(const std::string &name, const glm::mat4 &matrix);
    void set_uniform(const std::string &name, const glm::vec3 &vector);
    void set_uniform(const std::string &name, float scalar);
    void set_uniform(const std::string &name, int scalar);

    static ShaderProgram load_from_files(const std::string &vertex, const std::string &fragment);

private:
    GLint get_uniform_location(const std::string &name);

    Shader m_vertex_shader;
    Shader m_fragment_shader;
    std::unordered_map<std::string, GLint> m_uniform_locations;

};


#endif // OPENWAY_SHADER_PROGRAM_HPP
