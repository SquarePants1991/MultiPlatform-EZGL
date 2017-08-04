//
// Created by wang yang on 2017/8/2.
//

#ifndef EZGL_LAMBERTBLINNRENDERERTESTS_H
#define EZGL_LAMBERTBLINNRENDERERTESTS_H

#include "TestScene.h"
#include "renderer/ELLambertBlinnRenderer.h"

class LambertBlinnRendererTests: public TestScene {
public:
    LambertBlinnRendererTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    virtual void update(ELFloat deltaTime);

private:
    ELLambertBlinnRendererPtr lambertBlinnRenderer;
    ELVertexBufferPtr cubeVertexBuffer;
    ELCompositionVertexBufferPtr sphereVertexBuffer;
    ELTexturePtr diffuseTexture;
};

#endif //EZGL_LAMBERTBLINNRENDERERTESTS_H
