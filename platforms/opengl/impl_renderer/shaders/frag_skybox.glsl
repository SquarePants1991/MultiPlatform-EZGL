// defines
#version 330 core
precision highp float;
out vec4 fragColor;

struct LightInfo {
    int lightType; // 0 direct light 1 point light
    vec3 pose; // direct light => direction | point light => position
    float indensity; // 强度
    vec3 color; // 颜色
};

struct Material {
    vec3 diffuseColor;
    bool useDiffuseMap;
    vec3 ambientColor;
    vec3 specularColor;
    float specularIndensity;
    float smoothness; // 0 ~ 1000 越高显得越光滑
};

in vec4 position;
in vec3 normal;
in vec2 texcoord;
in vec3 tangent;
in vec3 bitangent;

uniform mat4 normalMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;

uniform Material material;

uniform sampler2D diffuseMap;
uniform bool useNormalMap;
uniform sampler2D normalMap;

#define MaxSupportLightCount 7
uniform LightInfo lights[MaxSupportLightCount]; // 最多支持7个灯光
uniform int lightCount;


uniform samplerCube skyBoxMap;

void main() {
    vec4 positionInWorld = modelMatrix * position;
    fragColor = texture(skyBoxMap, normalize(positionInWorld.xyz));
}