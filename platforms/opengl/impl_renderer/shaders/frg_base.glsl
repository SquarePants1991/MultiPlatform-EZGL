#version 330 core
precision highp float;
out vec4 fragColor;

in vec4 position;
in vec3 normal;
in vec2 texcoord;

uniform sampler2D diffuseMap;

void main() {
    vec4 surfaceColor = texture(diffuseMap, texcoord);
    if (surfaceColor.a <= 0.0) {
        discard;
    }
    fragColor = surfaceColor;
}