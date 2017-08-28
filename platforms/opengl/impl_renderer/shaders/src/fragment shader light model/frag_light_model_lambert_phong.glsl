include(`fragment shader light model/frag_light_model_base.glsl')
include(`fragment shader components/frag_shadow.glsl')

void light(out vec3 diffuseColor, out vec3 ambientColor,  out vec3 specularColor, vec3 normal) {
    float shadow = shadowIndensity();
    lambert(diffuseColor, normal);
    diffuseColor = diffuseColor * shadow;
    ambient(ambientColor);
    phong(specularColor, normal, eyeVector);
}

void surfaceColorPass(inout vec3 surfaceColor) {

}