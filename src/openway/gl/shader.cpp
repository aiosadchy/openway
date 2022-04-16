#include "openway/gl/shader.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/glad.h>


Shader::ShaderCompilationError::ShaderCompilationError(GLuint descriptor)
    : std::runtime_error("shader compilation error"), m_descriptor(descriptor) {
}

GLuint Shader::ShaderCompilationError::get_descriptor() const {
    return m_descriptor;
}


Shader::Shader(GLenum type, std::string_view source)
    : Descriptor(glCreateShader(type))
    , m_type(type) {
    const GLchar *source_ptr = source.begin();
    const GLint length = source.length();

    glShaderSource(*this, 1, &source_ptr, &length);
    glCompileShader(*this);

    GLint success;
    glGetShaderiv(*this, GL_COMPILE_STATUS, &success);
    if (!success) {
        throw ShaderCompilationError{*this};
    }
}

Shader::~Shader() {
    if (is_initialized()) {
        glDeleteShader(*this);
    }
}

GLenum Shader::get_type() const {
    return m_type;
}

Shader Shader::load_from_file(GLenum type, const std::string &filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    try {
        return Shader{type, source};
    } catch (const ShaderCompilationError &error) {
        const GLsizei max_log_length = 1024;
        GLchar compilation_log[max_log_length + 1];
        glGetShaderInfoLog(error.get_descriptor(), max_log_length, NULL, compilation_log);

        // TODO: proper logging
        std::cerr << "Failed to compile shader \"" << filename << "\":" << std::endl;
        std::cerr << compilation_log << std::endl;
        std::throw_with_nested(std::runtime_error{"error compiling shader \"" + filename + "\""});
    }
}
