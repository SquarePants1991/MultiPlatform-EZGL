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


// functions
void transformNormal(out vec3 transformedNormal, vec3 originNormal) {
    transformedNormal = (normalMatrix * vec4(originNormal, 1.0)).xyz;
    transformedNormal = normalize(transformedNormal);
}

/// Normal Map Process
mat3 tbn() {
    vec3 transformedNormal = normalize((normalMatrix * vec4(normal, 1.0)).xyz);
    vec3 transformedTangent = normalize((normalMatrix * vec4(tangent, 1.0)).xyz);
    vec3 transformedBitangent = normalize((normalMatrix * vec4(bitangent, 1.0)).xyz);
    mat3 TBN = mat3(
                              transformedTangent,
                              transformedBitangent,
                              transformedNormal
                              );
    return TBN;
}

vec3 unpackNormal() {
    if (useNormalMap) {
        mat3 TBN = tbn();
        vec3 normalFromMap = (texture(normalMap, texcoord).rgb * 2.0 - 1.0);
        return TBN * normalFromMap;
    }
    vec3 transformedNormal = vec3(0.0);
    transformNormal(transformedNormal, normal);
    return transformedNormal;
}

vec4 worldVertexPosition;
vec3 eyeVector;

vec3 lightDirection(LightInfo light) {
    vec3 l = vec3(0);
    if (light.lightType == 0) {
        l = normalize(-light.pose);
    } else if (light.lightType == 1) {
        l = normalize(light.pose - worldVertexPosition.xyz);
    }
    return l;
}

void ambient(out vec3 outColor) {
    outColor = material.ambientColor;
}

void prepareLightBasis() {
    worldVertexPosition = modelMatrix * position;
    eyeVector = normalize(cameraPosition - worldVertexPosition.xyz);
}


void lambertPerLight(out vec3 outColor, LightInfo light, vec3 normalizedNormal) {
    vec3 lightVector = lightDirection(light);
    float diffuseStrength = clamp(dot(lightVector, normalizedNormal), 0.0, 1.0);
    outColor = light.color * light.indensity * diffuseStrength;
}

void lambert(out vec3 outColor, vec3 normalizedNormal) {
    outColor = vec3(0.0);
    vec3 diffusePerLight;
    for (int i = 0; i < lightCount; ++i) {
        LightInfo light = lights[i];
        lambertPerLight(diffusePerLight, light, normalizedNormal);
        outColor += diffusePerLight;
    }
}

void phongblinnPerLight(out vec3 outColor, LightInfo light, vec3 normalizedNormal, vec3 eyeVector) {
    vec3 lightVector = lightDirection(light);
    vec3 halfVector = normalize(lightVector + eyeVector);
    float specularStrength = clamp(dot(normalizedNormal, halfVector), 0.0, 1.0);
    specularStrength = pow(specularStrength, material.smoothness);
    outColor = specularStrength * material.specularColor * light.color * light.indensity * material.specularIndensity;
}

void phongblinn(out vec3 outColor, vec3 normalizedNormal, vec3 eyeVector) {
    outColor = vec3(0.0);
    vec3 specularPerLight;
    for (int i = 0; i < lightCount; ++i) {
        LightInfo light = lights[i];
        phongblinnPerLight(specularPerLight, light, normalizedNormal, eyeVector);
        outColor += specularPerLight;
    }
}


// light model
void light(out vec3 diffuseColor, out vec3 ambientColor,  out vec3 specularColor, vec3 normal);
void surfaceColorPass(inout vec3 surfaceColor);

void main() {
    vec3 transformedNormal = unpackNormal();
    prepareLightBasis();

    vec3 diffuseColor = vec3(0.0);
    vec3 ambientColor = vec3(0.0);
    vec3 specularColor = vec3(0.0);

    light(diffuseColor, ambientColor, specularColor, transformedNormal);

    vec3 surfaceColor = material.diffuseColor;
    if (material.useDiffuseMap) {
        surfaceColor = texture(diffuseMap, texcoord).rgb;
    }

    surfaceColorPass(surfaceColor);

    vec3 finalColor = diffuseColor * surfaceColor + ambientColor + specularColor;
    fragColor = vec4(finalColor, 1.0);
}

uniform sampler2D decalMap;
uniform float decalAlpha;
uniform mat4 decalProjectionMatrix;

void decal(inout vec3 inputColor) {
    vec4 positionInDecalSpace = decalProjectionMatrix * modelMatrix * position;
    positionInDecalSpace = positionInDecalSpace / positionInDecalSpace.w;
    positionInDecalSpace = (positionInDecalSpace + 1.0) * 0.5;
    if (positionInDecalSpace.s >= 0 && positionInDecalSpace.s <= 1 &&
        positionInDecalSpace.t >= 0 && positionInDecalSpace.t <= 1 ) {
        vec4 decalColor = texture(decalMap, positionInDecalSpace.st);
        inputColor = decalColor.rgb * decalAlpha + inputColor * (1.0 - decalAlpha);
    }
}


void light(out vec3 diffuseColor, out vec3 ambientColor,  out vec3 specularColor, vec3 normal) {
    lambert(diffuseColor, normal);
    ambient(ambientColor);
    phongblinn(specularColor, normal, eyeVector);
}

void surfaceColorPass(inout vec3 surfaceColor) {
    decal(surfaceColor);
}
