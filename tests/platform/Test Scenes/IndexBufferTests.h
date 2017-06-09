//
// Created by wangyang on 2017/6/9.
//

#ifndef EZGL_INDEXBUFFERTESTS_H
#define EZGL_INDEXBUFFERTESTS_H

#include "../TestScene.h"

class IndexBufferTests: public TestScene {
public:
    IndexBufferTests();
    virtual void update(ELFloat deltaTime);

private:
    ELRenderPiplinePtr pipline;
    ELRenderPassPtr mainRenderPass;
    ELRendererPtr renderer;
    ELVertexBufferPtr cubeVertexBuffer;
    ELTexturePtr diffuseTexture;
};


#endif //EZGL_INDEXBUFFERTESTS_H
