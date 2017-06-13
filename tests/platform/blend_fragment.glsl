#version 330 core
precision highp float;
out vec4 outColor;

in vec3 fragColor;
in vec2 fragUV;

uniform vec4 color;

void main() {
    outColor = color;
}