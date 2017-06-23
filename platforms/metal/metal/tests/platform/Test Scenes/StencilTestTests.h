//
// Created by wang yang on 2017/6/19.
//

#ifndef EZGL_STENCILTESTTESTS_H
#define EZGL_STENCILTESTTESTS_H


#include "../TestScene.h"

class StencilTestTests: public TestScene {
public:
    StencilTestTests();
    virtual void update(ELFloat deltaTime);

private:
    ELRenderPiplinePtr pipline;
    ELRenderPassPtr mainRenderPass;
    ELRendererPtr renderer;
    ELCompositionVertexBufferPtr cubeVertexBuffer;
    ELVertexBufferPtr squareVertexBuffer;
    ELTexturePtr diffuseTexture;
};


#endif //EZGL_STENCILTESTTESTS_H
