//
// Created by wang yang on 2017/6/13.
//

#ifndef EZGL_BLENDMODETESTS_H
#define EZGL_BLENDMODETESTS_H

#include "TestScene.h"

class BlendModeTests: public TestScene {
public:
    BlendModeTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    virtual void update(ELFloat deltaTime);

private:
    ELRenderPiplinePtr pipline;
    ELRenderPassPtr mainRenderPass;
    ELRendererPtr renderer;
    ELVertexBufferPtr cubeVertexBuffer;
    ELTexturePtr diffuseTexture;
};


#endif //EZGL_BLENDMODETESTS_H
