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

    vec3 finalColor = diffuseColor * surfaceColor + ambientColor * surfaceColor + specularColor;
    fragColor = vec4(finalColor, 1.0);
}
