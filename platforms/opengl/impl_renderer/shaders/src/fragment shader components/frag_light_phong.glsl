void phongPerLight(out vec3 outColor, LightInfo light, vec3 normalizedNormal, vec3 eyeVector) {
    vec3 lightVector = lightDirection(light);
    vec3 reflectVector = normalize(reflect(-lightVector, normalizedNormal));
    float specularStrength = clamp(dot(eyeVector, reflectVector), 0.0, 1.0);
    specularStrength = pow(specularStrength, material.smoothness);
    outColor = specularStrength * material.specularColor * light.color * light.indensity * material.specularIndensity;
}

void phong(out vec3 outColor, vec3 normalizedNormal, vec3 eyeVector) {
    outColor = vec3(0.0);
    vec3 specularPerLight;
    for (int i = 0; i < lightCount; ++i) {
        LightInfo light = lights[i];
        phongPerLight(specularPerLight, light, normalizedNormal, eyeVector);
        outColor += specularPerLight;
    }
}
