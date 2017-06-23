//
// Created by wang yang on 2017/5/23.
//

#include "ELMetalAdapter.h"

ELMetalAdapter * ELMetalAdapter::_defaultAdapter = NULL;

ELMetalAdapter * ELMetalAdapter::defaultAdapter() {
    if ( ELMetalAdapter::_defaultAdapter == NULL) {
        ELMetalAdapter::_defaultAdapter = new ELMetalAdapter();
    }
    return _defaultAdapter;
}

void ELMetalAdapter::setup(id<MetalRenderContextProvider> renderContextProvider, id<MTLDevice> metalDevice, ELVector2 viewportSize) {
    this->renderContextProvider = renderContextProvider;
    this->metalDevice = metalDevice;
    
    this->defaultFBSize = viewportSize;
    // TODO: Fix These
    this->enableDepthBuffer = (renderContextProvider.currentRenderPassDescriptor.depthAttachment != nil);
    this->enableStencilBuffer = (renderContextProvider.currentRenderPassDescriptor.stencilAttachment != nil);
    // TODO: Map MTLPixelFormat to ELPixelFormat
    MTLPixelFormat pixelFormat = renderContextProvider.colorPixelFormat;
    this->defaultPixelFormat = ELPixelFormatRGBA;
}
