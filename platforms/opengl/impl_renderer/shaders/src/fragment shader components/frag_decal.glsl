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
