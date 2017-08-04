//
// Created by wang yang on 2017/8/4.
//

#ifndef EZGL_LAMBERTPHONGNORMALMAPTESTS_H
#define EZGL_LAMBERTPHONGNORMALMAPTESTS_H


#include "TestScene.h"
#include "renderer/ELLambertPhongRenderer.h"

class LambertPhongNormalMapTests: public TestScene {
public:
    LambertPhongNormalMapTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    virtual void update(ELFloat deltaTime);

private:
    ELLambertPhongRendererPtr lambertPhongRenderer;
    ELVertexBufferPtr cubeVertexBuffer;
    ELCompositionVertexBufferPtr sphereVertexBuffer;
    ELTexturePtr diffuseTexture;
    ELTexturePtr normalTexture;
};


#endif //EZGL_LAMBERTPHONGNORMALMAPTESTS_H
