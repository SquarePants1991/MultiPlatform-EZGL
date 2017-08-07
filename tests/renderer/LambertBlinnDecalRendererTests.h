//
// Created by wang yang on 2017/8/7.
//

#ifndef EZGL_LAMBERTBLINNDECALRENDERERTESTS_H
#define EZGL_LAMBERTBLINNDECALRENDERERTESTS_H

#include "TestScene.h"
#include "renderer/ELLambertBlinnDecalRenderer.h"

class LambertBlinnDecalRendererTests: public TestScene {
public:
    LambertBlinnDecalRendererTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    virtual void update(ELFloat deltaTime);

private:
    ELLambertBlinnDecalRendererPtr lambertBlinnDecalRenderer;
    ELVertexBufferPtr cubeVertexBuffer;
    ELCompositionVertexBufferPtr sphereVertexBuffer;
    ELTexturePtr diffuseTexture;
    ELTexturePtr decalTexture;
};

#endif //EZGL_LAMBERTBLINNDECALRENDERERTESTS_H
