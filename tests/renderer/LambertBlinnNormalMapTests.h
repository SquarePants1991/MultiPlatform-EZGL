//
// Created by wang yang on 2017/8/4.
//

#ifndef EZGL_LAMBERTBLINNNORMALMAPTESTS_H
#define EZGL_LAMBERTBLINNNORMALMAPTESTS_H

#include "TestScene.h"
#include "renderer/ELLambertBlinnRenderer.h"

class LambertBlinnNormalMapTests: public TestScene {
public:
    LambertBlinnNormalMapTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    virtual void update(ELFloat deltaTime);

private:
    ELLambertBlinnRendererPtr lambertBlinnRenderer;
    ELVertexBufferPtr cubeVertexBuffer;
    ELCompositionVertexBufferPtr sphereVertexBuffer;
    ELTexturePtr diffuseTexture;
    ELTexturePtr normalTexture;
};


#endif //EZGL_LAMBERTBLINNNORMALMAPTESTS_H
