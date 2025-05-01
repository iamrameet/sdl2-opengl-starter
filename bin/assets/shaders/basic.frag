#version 330 core

in vec3 fragColor;
out vec4 FragColor;

uniform float globalAlpha = 1.0;

void main() {
    FragColor = vec4(fragColor, globalAlpha);
}
