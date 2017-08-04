//
// Created by wang yang on 2017/8/2.
//

#ifndef EZGL_ELLAMBERTBLINNRENDERER_H
#define EZGL_ELLAMBERTBLINNRENDERER_H

#include "ELLambertPhongRenderer.h"

classDefExt(ELLambertBlinnRenderer, public ELLambertPhongRenderer)
public:
    ELLambertBlinnRendererPtr init(ELRenderPassConfig renderPassConfig, ELRenderTargetPtr renderTarget) {
        initPipline();
        ELRenderPassPtr renderPass = ELRenderPass::alloc()->init(renderPassConfig, renderTarget);
        renderer = ELRenderer::alloc()->init(renderPass, pipline);
        return selv;
    }
private:
    // pipline的实现因平台而异
    void initPipline();
defEnd

#endif //EZGL_ELLAMBERTBLINNRENDERER_H
