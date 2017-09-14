// defines
include(`fragment shader components/frag_base_header.glsl')
include(`fragment shader components/frag_structs.glsl')
include(`fragment shader components/frag_in_vars.glsl')
include(`fragment shader components/frag_uniform_vars.glsl')

uniform samplerCube skyBoxMap;

void main() {
   vec4 positionInWorld = modelMatrix * position;
   fragColor = texture(skyBoxMap, normalize(positionInWorld.xyz));
}