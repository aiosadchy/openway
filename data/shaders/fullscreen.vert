#version 330 core

layout (location = 0) in vec3 in_position;

out vec2 vert_uv;

void main() {
    vert_uv = 0.5 * (in_position.xy + vec2(1.0, 1.0));
    gl_Position = vec4(in_position.xy, 0.0, 1.0);
}

