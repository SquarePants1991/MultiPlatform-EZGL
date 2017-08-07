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
