include(`fragment shader light model/frag_light_model_base.glsl')

void light(out vec3 diffuseColor, out vec3 ambientColor,  out vec3 specularColor, vec3 normal) {
    lambert(diffuseColor, normal);
    ambient(ambientColor);
    phongblinn(specularColor, normal, eyeVector);
}

void surfaceColorPass(inout vec3 surfaceColor) {

}