//
// Created by wangyang on 2017/5/23.
//

#include "platform/ELRenderTarget.h"
#import "ELMetalAdapter.h"
#import "NSObjectHolder.h"
#import "ELTexture.h"

crossplatform_var_obj(drawable)
crossplatform_var_bool(isDefaultTarget)

ELRenderTargetPtr ELRenderTarget::init(ELPixelFormat pixelFormat, ELVector2 size, bool bindTexture, bool bindDepthTexture, bool enableDepthBuffer, bool enableStencilBuffer, bool enableColorBuffer) {
    isDefaultTargetSet(this, false);
    
    selv->pixelFormat = pixelFormat;
    selv->size = size;
    selv->colorBufferEnabled = true;
    selv->depthBufferEnabled = enableDepthBuffer;
    
    // bindTexture 忽略，全部都有Texture
    // 由于必须和piplineState里的数据一致，所以必须有colorAttachment
    if (true) {
        ELTexturePtr colorTexture = ELTexture::alloc()->init(ELPixelFormatRGBA, NULL, size.x, size.y);
        selv->bindTexture = colorTexture;
        selv->isBindTexture = true;
    }
    
    // Metal里暂时无视StencilBuffer是否Enable
    // 由于必须和piplineState里的数据一致，所以必须有depthAttachment
    if (true) {
        ELTexturePtr depthTexture = ELTexture::alloc()->init(ELPixelFormatDepth, NULL, size.x, size.y);
        selv->bindDepthTexture = depthTexture;
        selv->isBindDepthTexture = true;
    }
    return selv;
}

ELRenderTargetPtr ELRenderTarget::defaultTarget() {
    static ELRenderTargetPtr _defaultTarget;
    if (!_defaultTarget) {
        _defaultTarget = ELRenderTarget::alloc()->init(ELPixelFormatRGBA, ELMetalAdapter::defaultAdapter()->defaultFBSize, false);
        _defaultTarget->__crossplatformAttach("isDefaultTarget", true);
    }
    return _defaultTarget;
}

ELRenderTarget::~ELRenderTarget() {
    
}
