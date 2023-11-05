#ifndef OPENWAY_INCLUDE_OPENWAY_GL_SHADER_HPP
#define OPENWAY_INCLUDE_OPENWAY_GL_SHADER_HPP

#include <stdexcept>
#include <string>
#include <string_view>

#include <utl/default_movable.hpp>

#include "openway/gl/gl_object.hpp"

class Shader : public GLObject<GLuint> {
public:
    class CompilationError : public std::runtime_error {
    public:
        explicit CompilationError(GLuint descriptor);
        GLuint get_descriptor() const;

    private:
        GLuint m_descriptor;
    };

    Shader(GLenum type, std::string_view source);
    ~Shader();

    DEFAULT_MOVABLE(Shader)

    GLenum get_type() const;

    static Shader load_from_file(GLenum type, const std::string &filename);

private:
    GLenum m_type;
};

#endif // OPENWAY_INCLUDE_OPENWAY_GL_SHADER_HPP
