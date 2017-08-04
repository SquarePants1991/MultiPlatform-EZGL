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

    void setNormalMap(ELTexturePtr bumpMap) {
        setNormalMapEnable(true);
        pipline->bindTexture(bumpMap, pipline->getUniformLocation("normalMap"), 1);
    }

    void setNormalMapEnable(bool enabled) {
        pipline->setUniform((ELInt)enabled, pipline->getUniformLocation("useNormalMap"));
    }

    void setVertexBuffer(ELVertexBufferPtr vertexBuffer) {
        _currentDrawVertexBuffer = vertexBuffer;
        _currentDrawCompositionVertexBuffer = NULL;
    }

    void setVertexBuffer(ELCompositionVertexBufferPtr vertexBuffer) {
        _currentDrawCompositionVertexBuffer = vertexBuffer;
        _currentDrawVertexBuffer = NULL;
    }

    void setModelMatrix(ELMatrix4 modelMatrix) {
        pipline->setUniform(modelMatrix, pipline->getUniformLocation("modelMatrix"));
    }

    void setNormalMatrix(ELMatrix4 normalMatrix) {
        pipline->setUniform(normalMatrix, pipline->getUniformLocation("normalMatrix"));
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
        if (_currentDrawCompositionVertexBuffer) {
            renderer->drawPrimitives(primitivesType, _currentDrawCompositionVertexBuffer);
        }
    }

private:
    // pipline的实现因平台而异
    void initPipline();
    ELVertexBufferPtr _currentDrawVertexBuffer;
    ELCompositionVertexBufferPtr _currentDrawCompositionVertexBuffer;
defEnd


#endif //EZGL_BASEPIPLINE_H
