#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 fragColor;

uniform mat4 model;
uniform mat4 projection;
uniform vec3 color;

void main() {
    gl_Position = projection * model * vec4(aPos, 1.0);
    fragColor = color;
}
