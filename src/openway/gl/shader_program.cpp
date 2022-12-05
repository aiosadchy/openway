#include "openway/gl/shader_program.hpp"

#include <utility>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "openway/gl/call.hpp"
#include "openway/utility/log.hpp"

namespace {

#define DEFINE_UNIFORM_SETTER(value_type, function_suffix, ...)          \
    void operator()(const value_type &v) const {                         \
        OW_GL_CALL(glUniform##function_suffix(m_location, __VA_ARGS__)); \
    }

class UniformSetter {
public:
    explicit UniformSetter(GLint location)
    : m_location{location} {
    }

    DEFINE_UNIFORM_SETTER(GLfloat, 1f, v)
    DEFINE_UNIFORM_SETTER(glm::vec1, 1f, v.x)
    DEFINE_UNIFORM_SETTER(glm::vec2, 2f, v.x, v.y)
    DEFINE_UNIFORM_SETTER(glm::vec3, 3f, v.x, v.y, v.z)
    DEFINE_UNIFORM_SETTER(glm::vec4, 4f, v.x, v.y, v.z, v.w)
    DEFINE_UNIFORM_SETTER(GLint, 1i, v)
    DEFINE_UNIFORM_SETTER(glm::ivec1, 1i, v.x)
    DEFINE_UNIFORM_SETTER(glm::ivec2, 2i, v.x, v.y)
    DEFINE_UNIFORM_SETTER(glm::ivec3, 3i, v.x, v.y, v.z)
    DEFINE_UNIFORM_SETTER(glm::ivec4, 4i, v.x, v.y, v.z, v.w)
    DEFINE_UNIFORM_SETTER(GLuint, 1i, v)
    DEFINE_UNIFORM_SETTER(glm::uvec1, 1i, v.x)
    DEFINE_UNIFORM_SETTER(glm::uvec2, 2i, v.x, v.y)
    DEFINE_UNIFORM_SETTER(glm::uvec3, 3i, v.x, v.y, v.z)
    DEFINE_UNIFORM_SETTER(glm::uvec4, 4i, v.x, v.y, v.z, v.w)
    DEFINE_UNIFORM_SETTER(glm::mat2, Matrix2fv, 1, 0, glm::value_ptr(v))
    DEFINE_UNIFORM_SETTER(glm::mat3, Matrix3fv, 1, 0, glm::value_ptr(v))
    DEFINE_UNIFORM_SETTER(glm::mat4, Matrix4fv, 1, 0, glm::value_ptr(v))
    DEFINE_UNIFORM_SETTER(glm::mat2x3, Matrix2x3fv, 1, 0, glm::value_ptr(v))
    DEFINE_UNIFORM_SETTER(glm::mat3x2, Matrix3x2fv, 1, 0, glm::value_ptr(v))
    DEFINE_UNIFORM_SETTER(glm::mat2x4, Matrix2x4fv, 1, 0, glm::value_ptr(v))
    DEFINE_UNIFORM_SETTER(glm::mat4x2, Matrix4x2fv, 1, 0, glm::value_ptr(v))
    DEFINE_UNIFORM_SETTER(glm::mat3x4, Matrix3x4fv, 1, 0, glm::value_ptr(v))
    DEFINE_UNIFORM_SETTER(glm::mat4x3, Matrix4x3fv, 1, 0, glm::value_ptr(v))

private:
    GLint m_location;
};

#undef DEFINE_UNIFORM_SETTER

} // namespace

ShaderProgram::LinkingError::LinkingError(GLuint descriptor)
: std::runtime_error{"shader program linking error"}
, m_descriptor{descriptor} {
}

GLuint ShaderProgram::LinkingError::get_descriptor() const {
    return m_descriptor;
}

ShaderProgram::ShaderProgram(Shader &&vertex, Shader &&fragment)
: GLObject{OW_GL_CALL(glCreateProgram())}
, m_vertex_shader{std::move(vertex)}
, m_fragment_shader{std::move(fragment)}
, m_uniform_locations{} {
    OW_GL_CALL(glAttachShader(*this, m_vertex_shader));
    OW_GL_CALL(glAttachShader(*this, m_fragment_shader));
    OW_GL_CALL(glLinkProgram(*this));

    GLint success;
    OW_GL_CALL(glGetProgramiv(*this, GL_LINK_STATUS, &success));
    if (!success) {
        OW_LOG_THROW LinkingError{*this};
    }
}

ShaderProgram::~ShaderProgram() {
    if (*this) {
        OW_GL_CALL(glDeleteProgram(*this));
    }
}

void ShaderProgram::use() const {
    OW_GL_CALL(glUseProgram(*this));
}

void ShaderProgram::set_uniform(const std::string &name, const Uniform &uniform) {
    GLint location = get_uniform_location(name);
    // TODO: use glProgramUniform or something else to preserve uniform values
    std::visit(UniformSetter{location}, uniform);
}

GLint ShaderProgram::get_uniform_location(const std::string &name) {
    auto it = m_uniform_locations.find(name);
    if (it == m_uniform_locations.end()) {
        GLint loc = OW_GL_CALL(glGetUniformLocation(*this, name.c_str()));
        it        = m_uniform_locations.insert({name, loc}).first;
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
            Shader::load_from_file(GL_FRAGMENT_SHADER, fragment),
        };
    } catch (const LinkingError &error) {
        // TODO: remove this size gap, maybe move log to LinkingError
        const GLsizei max_log_length = 1024;
        GLchar compilation_log[max_log_length + 1];
        OW_GL_CALL(glGetProgramInfoLog(error.get_descriptor(), max_log_length, NULL, compilation_log));

        OW_LOG_ERROR("Failed to link program {\"", vertex, "\", \"", fragment, "\"}:\n", compilation_log);
        OW_LOG_THROW std::runtime_error{"error linking program {\"" + vertex + "\", \"" + fragment + "\"}"};
    }
}
