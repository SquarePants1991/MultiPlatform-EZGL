#version 330 core
precision highp float;
out vec4 outColor;

in vec3 fragColor;
in vec2 fragUV;

uniform sampler2D diffuse;

void main() {
    vec4 surfaceColor = texture(diffuse, fragUV);
    outColor = surfaceColor;
}