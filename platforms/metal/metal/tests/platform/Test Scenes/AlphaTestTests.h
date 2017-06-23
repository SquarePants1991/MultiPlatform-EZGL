//
// Created by wang yang on 2017/6/16.
//

#ifndef EZGL_ALPHATESTTESTS_H
#define EZGL_ALPHATESTTESTS_H

#include "../TestScene.h"

class AlphaTestTests: public TestScene {
public:
    AlphaTestTests();
    virtual void update(ELFloat deltaTime);

private:
    ELRenderPiplinePtr pipline;
    ELRenderPassPtr mainRenderPass;
    ELRendererPtr renderer;
    ELVertexBufferPtr cubeVertexBuffer;
    ELTexturePtr diffuseTexture;
};


#endif //EZGL_ALPHATESTTESTS_H
