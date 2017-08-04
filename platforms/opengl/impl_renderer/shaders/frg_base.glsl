#version 330 core
precision highp float;
out vec4 fragColor;

in vec4 position;
in vec3 normal;
in vec2 texcoord;
in vec3 tangent;
in vec3 bitangent;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

void main() {
    vec4 surfaceColor = texture(diffuseMap, texcoord);
    if (surfaceColor.a <= 0.0) {
        discard;
    }
    fragColor = surfaceColor;
}