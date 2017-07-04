#version 330 core
in vec4 v_position;
in vec3 v_normal;
in vec2 v_texcoord;

uniform mat4 normalMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 position;
out vec3 normal;
out vec2 texcoord;

void main() {
    mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
    position = v_position;
    normal = v_normal;
    texcoord = v_texcoord;
    gl_Position = mvp * position;
}