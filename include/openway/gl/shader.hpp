#ifndef OPENWAY_SHADER_HPP
#define OPENWAY_SHADER_HPP

#include <string>
#include <string_view>
#include <stdexcept>

#include <utl/default_movable.hpp>

#include "openway/gl/descriptor.hpp"


class Shader : public Descriptor<GLuint> {
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


#endif // OPENWAY_SHADER_HPP
