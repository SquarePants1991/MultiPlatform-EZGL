//
// Created by wang yang on 2017/6/22.
//

#ifndef EZGL_DEPTHTESTTESTS_H
#define EZGL_DEPTHTESTTESTS_H

#include "../TestScene.h"

class DepthTestTests: public TestScene {
public:
    DepthTestTests();
    virtual void update(ELFloat deltaTime);

private:
    ELRenderPiplinePtr pipline;
    ELRenderPassPtr mainRenderPass;
    ELRendererPtr renderer;
    ELVertexBufferPtr cubeVertexBuffer;
    ELTexturePtr diffuseTexture;
};


#endif //EZGL_DEPTHTESTTESTS_H
