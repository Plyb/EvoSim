#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 model;
uniform mat4 projection;

void main() {
    gl_Position = projection * model * vec4(pos, 0.0, 1.0);
    color = aColor;
}