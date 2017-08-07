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
