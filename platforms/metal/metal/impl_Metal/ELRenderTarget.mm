//
// Created by wangyang on 2017/5/23.
//

#include "platform/ELRenderTarget.h"
#import "ELMetalAdapter.h"
#import "NSObjectHolder.h"

crossplatform_var_obj(drawable)
crossplatform_var_bool(isDefaultTarget)

ELRenderTargetPtr ELRenderTarget::init(ELPixelFormat pixelFormat, ELVector2 size, bool bindTexture, bool bindDepthTexture, bool enableDepthBuffer, bool enableStencilBuffer, bool enableColorBuffer) {
    isDefaultTargetSet(this, false);
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
