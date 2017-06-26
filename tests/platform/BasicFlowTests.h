//
// Created by wangyang on 2017/6/7.
//

#ifndef EZGL_BASICFLOWTESTS_H
#define EZGL_BASICFLOWTESTS_H

#include "TestScene.h"

class BasicFlowTests : public TestScene {

public:
    BasicFlowTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    virtual void update(ELFloat deltaTime);

private:
    ELRenderPiplinePtr pipline;
    ELRenderPassPtr mainRenderPass;
    ELRendererPtr renderer;
    ELVertexBufferPtr cubeVertexBuffer;
    ELVertexBufferPtr squareVertexBuffer;
    ELTexturePtr diffuseTexture;

    ELRenderTargetPtr renderToTextureTarget;
    ELRenderPassPtr renderToTextureRenderPass;
    ELRendererPtr renderToTextureRender;

    ELRenderTargetPtr renderToDepthTextureTarget;
    ELRenderPassPtr renderToDepthTextureRenderPass;
    ELRendererPtr renderToDepthTextureRender;
};


#endif //EZGL_BASICFLOWTESTS_H
