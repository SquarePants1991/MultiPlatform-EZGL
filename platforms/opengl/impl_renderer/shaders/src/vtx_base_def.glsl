#version 330 core
in vec4 v_position;
in vec3 v_normal;
in vec2 v_texcoord;
in vec3 v_tangent;
in vec3 v_bitangent;

uniform mat4 normalMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 position;
out vec3 normal;
out vec2 texcoord;
out vec3 tangent;
out vec3 bitangent;

void main() {
    mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
    position = v_position;
    normal = v_normal;
    texcoord = v_texcoord;
    tangent = v_tangent;
    bitangent = v_bitangent;
    gl_Position = mvp * position;
}
