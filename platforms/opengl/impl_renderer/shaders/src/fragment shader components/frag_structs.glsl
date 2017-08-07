struct LightInfo {
    int lightType; // 0 direct light 1 point light
    vec3 pose; // direct light => direction | point light => position
    float indensity; // 强度
    vec3 color; // 颜色
};

struct Material {
    vec3 diffuseColor;
    bool useDiffuseMap;
    vec3 ambientColor;
    vec3 specularColor;
    float specularIndensity;
    float smoothness; // 0 ~ 1000 越高显得越光滑
};
