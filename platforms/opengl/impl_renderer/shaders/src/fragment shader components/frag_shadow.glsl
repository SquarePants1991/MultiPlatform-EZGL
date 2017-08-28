uniform sampler2D shadowMap;
uniform bool shadowEnabled;
uniform mat4 lightProjectionMatrix;


float shadowIndensity() {
    if (shadowEnabled == false) {
        return 1.0;
    }
    float bias = 0.001;
    vec4 positionInLightSpace = lightProjectionMatrix * modelMatrix * position;
    positionInLightSpace = positionInLightSpace / positionInLightSpace.w;
    positionInLightSpace = (positionInLightSpace + 1.0) * 0.5;
    if (positionInLightSpace.s >= 0 && positionInLightSpace.s <= 1 &&
        positionInLightSpace.t >= 0 && positionInLightSpace.t <= 1 ) {
        float nearestDepth = texture(shadowMap, positionInLightSpace.st).r;
        if (positionInLightSpace.z > nearestDepth + bias ) {
            return 0.4;
        }
    }
    return 1.0;
}
