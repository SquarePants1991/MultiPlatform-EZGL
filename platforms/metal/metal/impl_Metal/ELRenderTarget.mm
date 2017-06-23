//
// Created by wangyang on 2017/5/23.
//

#include "platform/ELRenderTarget.h"
#import "ELMetalAdapter.h"
#import "NSObjectHolder.h"

crossplatform_var_obj(drawable)

ELRenderTargetPtr ELRenderTarget::init(ELPixelFormat pixelFormat, ELVector2 size, bool bindTexture, bool bindDepthTexture, bool enableDepthBuffer, bool enableStencilBuffer, bool enableColorBuffer) {
    return selv;
}

ELRenderTargetPtr ELRenderTarget::defaultTarget() {
    static ELRenderTargetPtr _defaultTarget;
    if (!_defaultTarget) {
        _defaultTarget = ELRenderTarget::alloc()->init(ELPixelFormatRGBA, ELMetalAdapter::defaultAdapter()->defaultFBSize, false);
        id <MTLDrawable> drawable = ELMetalAdapter::defaultAdapter()->renderContextProvider.currentDrawable;
        MTLRenderPassDescriptor *defaultRenderPassDesc = ELMetalAdapter::defaultAdapter()->renderContextProvider.currentRenderPassDescriptor;
        _defaultTarget->__crossplatformAttach("drawable", (__bridge void *)drawable);
        _defaultTarget->__crossplatformAttach("defaultRenderPassDesc", (__bridge void *)defaultRenderPassDesc);
        
        [NSObjectHolder retain: drawable];
        [NSObjectHolder retain: defaultRenderPassDesc];
    }
    return _defaultTarget;
}

ELRenderTarget::~ELRenderTarget() {
    
}
