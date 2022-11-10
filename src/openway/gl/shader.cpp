#include "openway/gl/shader.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/glad.h>

#include "openway/log.hpp"


Shader::CompilationError::CompilationError(GLuint descriptor)
    : std::runtime_error("shader compilation error")
    , m_descriptor(descriptor) {
}

GLuint Shader::CompilationError::get_descriptor() const {
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
        throw CompilationError{*this};
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
    } catch (const CompilationError &error) {
        const GLsizei max_log_length = 1024;
        GLchar compilation_log[max_log_length + 1];
        glGetShaderInfoLog(error.get_descriptor(), max_log_length, NULL, compilation_log);

        OW_LOG_ERROR("Failed to compile shader \"", filename, "\":\n", compilation_log);
        std::throw_with_nested(
            std::runtime_error{"error compiling shader \"" + filename + "\""}
        );
    }
}
