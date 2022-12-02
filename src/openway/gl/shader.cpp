#include "openway/gl/shader.hpp"

#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "openway/gl/call.hpp"
#include "openway/utility/log.hpp"

Shader::CompilationError::CompilationError(GLuint descriptor)
: std::runtime_error("shader compilation error")
, m_descriptor(descriptor) {
}

GLuint Shader::CompilationError::get_descriptor() const {
    return m_descriptor;
}

Shader::Shader(GLenum type, std::string_view source)
: Descriptor(OW_GL_CALL(glCreateShader(type)))
, m_type(type) {
    const GLchar *source_ptr = source.begin();
    const GLint length       = source.length();

    OW_GL_CALL(glShaderSource(*this, 1, &source_ptr, &length));
    OW_GL_CALL(glCompileShader(*this));

    GLint success;
    OW_GL_CALL(glGetShaderiv(*this, GL_COMPILE_STATUS, &success));
    if (!success) {
        OW_LOG_THROW CompilationError{*this};
    }
}

Shader::~Shader() {
    if (is_initialized()) {
        OW_GL_CALL(glDeleteShader(*this));
    }
}

GLenum Shader::get_type() const {
    return m_type;
}

Shader Shader::load_from_file(GLenum type, const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        OW_LOG_THROW std::runtime_error{"unable to open file \"" + filename + "\""};
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    try {
        return Shader{type, source};
    } catch (const CompilationError &error) {
        const GLsizei max_log_length = 1024;
        GLchar compilation_log[max_log_length + 1];
        OW_GL_CALL(glGetShaderInfoLog(error.get_descriptor(), max_log_length, NULL, compilation_log));

        OW_LOG_ERROR("Failed to compile shader \"", filename, "\":\n", compilation_log);
        OW_LOG_THROW std::runtime_error{"error compiling shader \"" + filename + "\""};
    }
}
