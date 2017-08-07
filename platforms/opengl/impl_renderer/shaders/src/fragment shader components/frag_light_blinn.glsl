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
