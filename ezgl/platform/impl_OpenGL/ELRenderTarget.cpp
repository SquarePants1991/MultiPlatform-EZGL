//
// Created by wangyang on 2017/5/23.
//

#include "../ELRenderTarget.h"
#include "ELGLAdapter.h"

crossplatform_var(ELInt, framebuffer)

ELRenderTargetPtr ELRenderTarget::init(ELPixelFormat pixelFormat, ELVector2 size, bool bindTexture, bool enableDepthBuffer, bool enableStencilBuffer) {
    this->pixelFormat = pixelFormat;
    this->size = size;
    this->isBindTexture = bindTexture;
    this->depthBufferEnabled = enableDepthBuffer;
    this->stencilBufferEnabled = enableStencilBuffer;
    //... impl framebuffer create
    return self;
}

ELRenderTargetPtr ELRenderTarget::defaultTarget() {
    static ELRenderTargetPtr defaultTarget;
    if (!defaultTarget) {
        defaultTarget = ELRenderTarget::alloc();
        ELGLAdapter *defaultAdapter = ELGLAdapter::defaultAdapter();

        framebufferSet(defaultTarget.get(), defaultAdapter->defaultFramebuffer);
        defaultTarget->size = defaultAdapter->defaultFBSize;
        defaultTarget->pixelFormat = defaultAdapter->defaultPixelFormat;
        defaultTarget->isBindTexture = false;
        defaultTarget->colorBufferEnabled = true;
        defaultTarget->depthBufferEnabled = true;
        defaultTarget->stencilBufferEnabled = true;
    }
    return defaultTarget;
}