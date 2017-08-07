//
// Created by wang yang on 2017/8/7.
//

#ifndef EZGL_ELLAMBERTBLINNDECALRENDERER_H
#define EZGL_ELLAMBERTBLINNDECALRENDERER_H

#include "ELLambertPhongRenderer.h"

classDefExt(ELLambertBlinnDecalRenderer, public ELLambertPhongRenderer)
public:
    ELLambertBlinnDecalRendererPtr init(ELRenderPassConfig renderPassConfig, ELRenderTargetPtr renderTarget) {
        initPipline();
        ELRenderPassPtr renderPass = ELRenderPass::alloc()->init(renderPassConfig, renderTarget);
        renderer = ELRenderer::alloc()->init(renderPass, pipline);
        return selv;
    }

    void setDecalMap(ELTexturePtr decalMap) {
        pipline->bindTexture(decalMap, pipline->getUniformLocation("decalMap"), 3);
    }

    void setDecalProjectionMatrix(ELMatrix4 projectionMatrix) {
        pipline->setUniform(projectionMatrix, pipline->getUniformLocation("decalProjectionMatrix"));
    }

    void setDecalAlpha(float decalAlpha) {
        pipline->setUniform(decalAlpha, pipline->getUniformLocation("decalAlpha"));
    }
private:
    // pipline的实现因平台而异
    void initPipline();
defEnd

#endif //EZGL_ELLAMBERTBLINNDECALRENDERER_H
