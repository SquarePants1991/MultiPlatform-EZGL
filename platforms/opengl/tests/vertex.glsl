#version 330 core
layout(location = 1) in vec4 position;
in vec3 color;
in vec2 uv;

uniform mat4 transform;

out vec3 fragColor;
out vec2 fragUV;

void main() {
    fragColor = vec3(uv, 1.0);
    fragUV = uv;
    gl_Position = transform * position;
}