//
// Created by wang yang on 2017/9/14.
//

#ifndef EZGL_ELSKYBOXRENDERER_H
#define EZGL_ELSKYBOXRENDERER_H

#import "../platform/ELCppBase.h"
#import "../platform/ELRenderPipline.h"
#import "../platform/ELRenderer.h"
#import "../platform/ELTexture.h"

#include "ELBaseRenderer.h"

classDefExt(ELSkyBoxRenderer, public ELBaseRenderer)

public:
    ELSkyBoxRendererPtr init(ELRenderPassConfig renderPassConfig, ELRenderTargetPtr renderTarget) {
        initPipline();
        ELRenderPassPtr renderPass = ELRenderPass::alloc()->init(renderPassConfig, renderTarget);
        renderer = ELRenderer::alloc()->init(renderPass, pipline);
        return selv;
    }

    // 替代基础renderer 0 通道上的diffuseMap
    void setSkyBoxCubeMap(ELTexturePtr cubeMap) {
        pipline->bindTexture(cubeMap, pipline->getUniformLocation("skyBoxMap"), 0);
    }

private:
    // pipline的实现因平台而异
    void initPipline();
defEnd

#endif //EZGL_ELSKYBOXRENDERER_H
