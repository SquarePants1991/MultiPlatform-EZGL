//
// Created by wang yang on 2017/7/4.
//

#ifndef EZGL_BASICRENDERERTESTS_H
#define EZGL_BASICRENDERERTESTS_H

#include "TestScene.h"
#include "renderer/ELBaseRenderer.h"

class BasicRendererTests: public TestScene {
public:
    BasicRendererTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    virtual void update(ELFloat deltaTime);

private:
    ELBaseRendererPtr baseRenderer;
    ELVertexBufferPtr cubeVertexBuffer;
    ELTexturePtr diffuseTexture;
};


#endif //EZGL_BASICRENDERERTESTS_H
