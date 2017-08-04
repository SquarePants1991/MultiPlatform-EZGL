//
// Created by wang yang on 2017/7/24.
//

#ifndef EZGL_ELLAMBERTPHONGRENDERER_H
#define EZGL_ELLAMBERTPHONGRENDERER_H

#import "ELBaseRenderer.h"

enum ELLightType {
    ELLightTypeDirect = 0,
    ELLightTypePoint = 1,
};

typedef struct {
    ELLightType lightType;
    ELVector3 pose; // direct light => direction | point light => position
    float indensity; // 强度
    ELVector3 color; // 颜色
}ELLightInfo;

typedef struct {
    ELVector3 diffuseColor;
    bool useDiffuseMap;
    bool useBumpMap;
    ELVector3 ambientColor;
    ELVector3 specularColor;
    float specularIndensity; // 0 ~ 1 控制高光强度
    float smoothness; // 0 ~ 1000 越高显得越光滑
}ELLambertPhongMaterial;

classDefExt(ELLambertPhongRenderer, public ELBaseRenderer)
public:
    ELLambertPhongRendererPtr init(ELRenderPassConfig renderPassConfig, ELRenderTargetPtr renderTarget) {
        initPipline();
        ELRenderPassPtr renderPass = ELRenderPass::alloc()->init(renderPassConfig, renderTarget);
        renderer = ELRenderer::alloc()->init(renderPass, pipline);
        return selv;
    }

    void setLights(ELLightInfo *lightInfo, int lightCount) {
        pipline->setUniform(lightCount, pipline->getUniformLocation("lightCount"));
        char uniformNameBuffer[255];
        for (int i = 0; i < lightCount; ++i) {
            ELLightInfo light = *(lightInfo + i);
            sprintf(uniformNameBuffer, "lights[%d].lightType", i);
            pipline->setUniform(light.lightType, pipline->getUniformLocation(uniformNameBuffer));
            sprintf(uniformNameBuffer, "lights[%d].pose", i);
            pipline->setUniform(light.pose, pipline->getUniformLocation(uniformNameBuffer));
            sprintf(uniformNameBuffer, "lights[%d].indensity", i);
            pipline->setUniform(light.indensity, pipline->getUniformLocation(uniformNameBuffer));
            sprintf(uniformNameBuffer, "lights[%d].color", i);
            pipline->setUniform(light.color, pipline->getUniformLocation(uniformNameBuffer));
        }
    }

    void setCameraPosition(ELVector3 cameraPosition) {
        pipline->setUniform(cameraPosition, pipline->getUniformLocation("cameraPosition"));
    }

    void setMaterial(ELLambertPhongMaterial material) {
        char uniformNameBuffer[255];
        sprintf(uniformNameBuffer, "material.diffuseColor");
        pipline->setUniform(material.diffuseColor, pipline->getUniformLocation(uniformNameBuffer));
        sprintf(uniformNameBuffer, "material.useDiffuseMap");
        pipline->setUniform((ELInt)material.useDiffuseMap, pipline->getUniformLocation(uniformNameBuffer));
        sprintf(uniformNameBuffer, "material.ambientColor");
        pipline->setUniform(material.ambientColor, pipline->getUniformLocation(uniformNameBuffer));
        sprintf(uniformNameBuffer, "material.specularColor");
        pipline->setUniform(material.specularColor, pipline->getUniformLocation(uniformNameBuffer));
        sprintf(uniformNameBuffer, "material.smoothness");
        pipline->setUniform(material.smoothness, pipline->getUniformLocation(uniformNameBuffer));
        sprintf(uniformNameBuffer, "material.specularIndensity");
        pipline->setUniform(material.specularIndensity, pipline->getUniformLocation(uniformNameBuffer));
    }

private:
    // pipline的实现因平台而异
    void initPipline();
defEnd

#endif //EZGL_ELLAMBERTPHONGRENDERER_H
