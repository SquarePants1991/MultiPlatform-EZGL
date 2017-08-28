//
// Created by wang yang on 2017/8/18.
//

#ifndef EZGL_LAMBERTPHONGSHADOWTESTS_H
#define EZGL_LAMBERTPHONGSHADOWTESTS_H

#include "TestScene.h"
#include "renderer/ELLambertPhongRenderer.h"

class LambertPhongShadowTests: public TestScene {
public:
    LambertPhongShadowTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    virtual void update(ELFloat deltaTime);

private:
    ELLambertPhongRendererPtr lambertPhongRenderer;
    ELVertexBufferPtr cubeVertexBuffer;
    ELCompositionVertexBufferPtr sphereVertexBuffer;
    ELTexturePtr diffuseTexture;
    ELRenderTargetPtr shadowMapRenderTarget;
    ELBaseRendererPtr shadowMapRenderer;

    ELLightInfo lightWithShadow;

    void setupShadowMapRenderer();
    void renderToShadowMap();
};


#endif //EZGL_LAMBERTPHONGSHADOWTESTS_H
