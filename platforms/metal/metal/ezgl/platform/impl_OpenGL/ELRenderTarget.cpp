//
// Created by wangyang on 2017/5/23.
//

#include "../ELRenderTarget.h"
#include "ELGLAdapter.h"

crossplatform_var_int(framebuffer)
crossplatform_var_int(texture)
crossplatform_var_int(colorBuffer)
crossplatform_var_int(depthBuffer)

ELRenderTargetPtr ELRenderTarget::init(ELPixelFormat pixelFormat, ELVector2 size, bool bindTexture, bool bindDepthTexture,bool enableDepthBuffer, bool enableStencilBuffer, bool enableColorBuffer) {
    this->pixelFormat = pixelFormat;
    this->size = size;
    this->isBindTexture = bindTexture;
    this->isBindDepthTexture = bindDepthTexture;
    this->colorBufferEnabled = enableColorBuffer;
    this->depthBufferEnabled = enableDepthBuffer;
    this->stencilBufferEnabled = enableStencilBuffer;

    colorBufferSet(this, -1);
    depthBufferSet(this, -1);
    textureSet(this, -1);

    GLuint framebuffer;
    GLuint texture;
    GLuint depthTexture;
    GLuint depthBuffer;
    GLuint colorBuffer;

    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);


    if (enableColorBuffer) {
        if (bindTexture) {
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
            textureSet(this, texture);
            this->bindTexture = ELTexture::alloc()->init(ELPixelFormatRGBA, NULL, size.x, size.y);
            this->bindTexture->__crossplatformAttach("glVal", (ELInt)texture);
        } else {
            glGenRenderbuffers(1, &colorBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, colorBuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, size.x, size.y);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBuffer);
            colorBufferSet(this, colorBuffer);
        }
    }

    if (enableDepthBuffer) {
        if (bindDepthTexture) {
            glGenTextures(1, &depthTexture);
            glBindTexture(GL_TEXTURE_2D, depthTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, size.x, size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
            this->bindDepthTexture = ELTexture::alloc()->init(ELPixelFormatDepth, NULL, size.x, size.y);
            this->bindDepthTexture->__crossplatformAttach("glVal", (ELInt)depthTexture);
        } else {
            glGenRenderbuffers(1, &depthBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
            if (enableStencilBuffer) {
                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
            } else {
                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, size.x, size.y);
            }

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
            depthBufferSet(this, depthBuffer);
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    framebufferSet(this, framebuffer);


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

ELRenderTarget::~ELRenderTarget() {
    ELInt framebuffer = framebufferGet(this);
    glDeleteFramebuffers(1, (GLuint *)&framebuffer);
}