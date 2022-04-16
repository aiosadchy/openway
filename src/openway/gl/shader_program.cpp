#include "openway/gl/shader_program.hpp"

#include <iostream>
#include <utility>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


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
        const GLsizei max_log_length = 1024;
        GLchar compilation_log[max_log_length + 1];
        glGetProgramInfoLog(*this, max_log_length, NULL, compilation_log);

        // TODO: proper logging
        std::cerr << "Failed to link shader program:" << std::endl;
        std::cerr << compilation_log << std::endl;

        throw std::runtime_error("error linking shader program");
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
