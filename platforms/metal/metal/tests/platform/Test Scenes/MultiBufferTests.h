//
// Created by wangyang on 2017/6/7.
//

#ifndef EZGL_MULTIBUFFERTESTS_H
#define EZGL_MULTIBUFFERTESTS_H

#include "../TestScene.h"

class MultiBufferTests: public TestScene {
public:
    MultiBufferTests();
    virtual void update(ELFloat deltaTime);

private:
    ELRenderPiplinePtr pipline;
    ELRenderPassPtr mainRenderPass;
    ELRendererPtr renderer;
    ELCompositionVertexBufferPtr cubeVertexBuffer;
    ELTexturePtr diffuseTexture;
};


#endif //EZGL_MULTIBUFFERTESTS_H
