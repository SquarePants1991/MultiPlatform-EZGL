uniform mat4 normalMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;

uniform Material material;

uniform sampler2D diffuseMap;
uniform bool useNormalMap;
uniform sampler2D normalMap;

#define MaxSupportLightCount 7
uniform LightInfo lights[MaxSupportLightCount]; // 最多支持7个灯光
uniform int lightCount;
