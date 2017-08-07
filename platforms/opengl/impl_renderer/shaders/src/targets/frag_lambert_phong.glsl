// defines
include(`fragment shader components/frag_base_header.glsl')
include(`fragment shader components/frag_structs.glsl')
include(`fragment shader components/frag_in_vars.glsl')
include(`fragment shader components/frag_uniform_vars.glsl')

// functions
include(`fragment shader components/frag_normal.glsl')
include(`fragment shader components/frag_light_base.glsl')
include(`fragment shader components/frag_light_lambert.glsl')
include(`fragment shader components/frag_light_phong.glsl')

// light model
include(`fragment shader light model/frag_light_model_lambert_phong.glsl')
