#ifndef OPENWAY_SHADER_HPP
#define OPENWAY_SHADER_HPP

#include <string>
#include <string_view>
#include <stdexcept>

#include "openway/gl/descriptor.hpp"


class Shader : public Descriptor<GLuint> {
public:
    class ShaderCompilationError : public std::runtime_error {
    public:
        explicit ShaderCompilationError(GLuint descriptor);
        GLuint get_descriptor() const;

    private:
        GLuint m_descriptor;

    };

    Shader(GLenum type, std::string_view source);
    ~Shader();

    static Shader load_from_file(GLenum type, const std::string &filename);

};


#endif // OPENWAY_SHADER_HPP
