#include "openway/gl/shader_program.hpp"

#include <exception>
#include <iostream>
#include <utility>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "openway/log.hpp"


ShaderProgram::LinkingError::LinkingError(GLuint descriptor)
    : std::runtime_error("shader program linking error")
    , m_descriptor(descriptor) {
}

GLuint ShaderProgram::LinkingError::get_descriptor() const {
    return m_descriptor;
}


ShaderProgram::ShaderProgram(Shader &&vertex, Shader &&fragment)
    : Descriptor(glCreateProgram())
    , m_vertex_shader(std::move(vertex))
    , m_fragment_shader(std::move(fragment))
    , m_uniform_locations() {
    glAttachShader(*this, m_vertex_shader);
    glAttachShader(*this, m_fragment_shader);
    glLinkProgram(*this);

    GLint success;
    glGetProgramiv(*this, GL_LINK_STATUS, &success);
    if(!success) {
        OW_LOG_THROW LinkingError{*this};
    }
}

ShaderProgram::~ShaderProgram() {
    if (is_initialized()) {
        glDeleteProgram(*this);
    }
}

void ShaderProgram::use() {
    glUseProgram(*this);
}

void ShaderProgram::set_uniform(const std::string &name, const glm::mat4 &matrix) {
    GLint location = get_uniform_location(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::set_uniform(const std::string &name, const glm::vec3 &vector) {
    GLint location = get_uniform_location(name);
    glUniform3fv(location, 1, glm::value_ptr(vector));
}

void ShaderProgram::set_uniform(const std::string &name, float scalar) {
    GLint location = get_uniform_location(name);
    glUniform1f(location, scalar);
}

void ShaderProgram::set_uniform(const std::string &name, int scalar) {
    GLint location = get_uniform_location(name);
    glUniform1i(location, scalar);
}

GLint ShaderProgram::get_uniform_location(const std::string &name) {
    auto it = m_uniform_locations.find(name);
    if (it == m_uniform_locations.end()) {
        GLint location = glGetUniformLocation(*this, name.c_str());
        it = m_uniform_locations.insert({name, location}).first;
    }
    return it->second;
}

ShaderProgram ShaderProgram::load_from_files(
        const std::string &vertex,
        const std::string &fragment
) {
    try {
        return ShaderProgram{
            Shader::load_from_file(GL_VERTEX_SHADER, vertex),
            Shader::load_from_file(GL_FRAGMENT_SHADER, fragment)
        };
    } catch (const LinkingError &error) {
        const GLsizei max_log_length = 1024;
        GLchar compilation_log[max_log_length + 1];
        glGetProgramInfoLog(error.get_descriptor(), max_log_length, NULL, compilation_log);

        OW_LOG_ERROR("Failed to link program [\"", vertex, "\", \"", fragment, "\"]:\n", compilation_log);
        std::throw_with_nested(
            std::runtime_error("error linking program [\"" + vertex + "\", \"" + fragment + "\"]")
        );
    }
}
