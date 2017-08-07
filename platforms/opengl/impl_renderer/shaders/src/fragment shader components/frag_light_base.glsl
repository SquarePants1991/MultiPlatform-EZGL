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

