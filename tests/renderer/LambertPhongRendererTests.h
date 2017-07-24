//
// Created by wang yang on 2017/7/24.
//

#ifndef EZGL_LAMBERTPHONGRENDERERTESTS_H
#define EZGL_LAMBERTPHONGRENDERERTESTS_H

#include "TestScene.h"
#include "renderer/ELLambertPhongRenderer.h"

class LambertPhongRendererTests: public TestScene {
public:
    LambertPhongRendererTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    virtual void update(ELFloat deltaTime);

private:
    ELLambertPhongRendererPtr lambertPhongRenderer;
    ELVertexBufferPtr cubeVertexBuffer;
    ELCompositionVertexBufferPtr sphereVertexBuffer;
    ELTexturePtr diffuseTexture;
};


#endif //EZGL_LAMBERTPHONGRENDERERTESTS_H
