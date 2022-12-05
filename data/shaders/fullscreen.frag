#version 330 core

in vec2 vert_uv;

out vec4 frag_color;

void main() {
    frag_color = vec4(vert_uv, 0, 1);
}
