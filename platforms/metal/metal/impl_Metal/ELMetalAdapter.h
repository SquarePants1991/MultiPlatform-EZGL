//
// Created by wang yang on 2017/5/23.
//

#ifndef EZGL_ELGLADAPTER_H
#define EZGL_ELGLADAPTER_H

#include "platform/types/EZGLTypes.h"

#import "MetalRenderContextProvider.h"
#import <Metal/Metal.h>
#import <Quartz/Quartz.h>

class ELMetalAdapter {
public:
    static ELMetalAdapter *defaultAdapter();
    void setup(id<MetalRenderContextProvider> renderContextProvider, id<MTLDevice> metalDevice, ELVector2 viewportSize);
    
    id<MetalRenderContextProvider> renderContextProvider;
    id<MTLDevice> metalDevice;
    ELVector2 defaultFBSize;
    bool enableDepthBuffer;
    bool enableStencilBuffer;
    ELPixelFormat defaultPixelFormat;
private:
    static ELMetalAdapter *_defaultAdapter;
};


#endif //EZGL_ELGLADAPTER_H
