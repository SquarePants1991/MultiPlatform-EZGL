//
// Created by wangyang on 2017/5/23.
//

#include "../ELRenderTarget.h"
#include "ELGLAdapter.h"

ELRenderTargetPtr ELRenderTarget::init(ELPixelFormat pixelFormat, ELVector2 size, bool bindTexture, bool enableDepthBuffer, bool enableStencilBuffer) {
    this->pixelFormat = pixelFormat;
    this->size = size;
    this->isBindTexture = bindTexture;
    this->depthBufferEnabled = enableDepthBuffer;
    this->stencilBufferEnabled = enableStencilBuffer;
    //... impl framebuffer create
}

ELRenderTargetPtr ELRenderTarget::defaultTarget() {

}