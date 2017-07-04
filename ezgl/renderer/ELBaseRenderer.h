//
// Created by wang yang on 2017/7/4.
//

#ifndef EZGL_BASEPIPLINE_H
#define EZGL_BASEPIPLINE_H

#import "../platform/ELCppBase.h"
#import "../platform/ELRenderPipline.h"
#import "../platform/ELRenderer.h"
#import "../platform/ELTexture.h"

classDef(ELBaseRenderer)

public:
    ELRenderPiplinePtr pipline;
    ELRendererPtr renderer;
public:
    ELBaseRendererPtr init(ELRenderPassConfig renderPassConfig, ELRenderTargetPtr renderTarget) {
        initPipline();
        ELRenderPassPtr renderPass = ELRenderPass::alloc()->init(renderPassConfig, renderTarget);
        renderer = ELRenderer::alloc()->init(renderPass, pipline);
        return selv;
    }

    void beginDraw() {
        renderer->prepare();
        renderer->enableDepthTest();
    }

    void commitDraw() {
        renderer->endRender();
    }

    void setDiffuseMap(ELTexturePtr diffuseMap) {
        pipline->bindTexture(diffuseMap, pipline->getUniformLocation("diffuseMap"), 0);
    }

    void setVertexBuffer(ELVertexBufferPtr vertexBuffer) {
        _currentDrawVertexBuffer = vertexBuffer;
    }

    void setModelMatrix(ELMatrix4 modelMatrix) {
        pipline->setUniform(modelMatrix, pipline->getUniformLocation("modelMatrix"));
    }

    void setViewMatrix(ELMatrix4 viewMatrix) {
        pipline->setUniform(viewMatrix, pipline->getUniformLocation("viewMatrix"));
    }

    void setProjectionMatrix(ELMatrix4 projectionMatrix) {
        pipline->setUniform(projectionMatrix, pipline->getUniformLocation("projectionMatrix"));
    }

    void draw(ELPrimitivesType primitivesType) {
        if (_currentDrawVertexBuffer) {
            renderer->drawPrimitives(primitivesType, _currentDrawVertexBuffer);
        }
    }

private:
    // pipline的实现因平台而异
    void initPipline();
    ELVertexBufferPtr _currentDrawVertexBuffer;
defEnd


#endif //EZGL_BASEPIPLINE_H
