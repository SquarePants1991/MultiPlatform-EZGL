//
// Created by wangyang on 2017/5/24.
//

#include "platform/ELRenderPipline.h"
#import "ELMetalAdapter.h"
#import "NSObjectHolder.h"

crossplatform_var_obj(piplineState)
crossplatform_var_obj(uniformBuffer)

ELRenderPiplinePtr ELRenderPipline::init(std::string vertexShader, std::string fragmentShader) {
    id <MTLDevice> device = ELMetalAdapter::defaultAdapter()->metalDevice;
    id <MetalRenderContextProvider> renderContextProvider = ELMetalAdapter::defaultAdapter()->renderContextProvider;
    
    id <MTLLibrary> defaultLibrary = [ELMetalAdapter::defaultAdapter()->metalDevice newDefaultLibrary];
    id <MTLFunction> vertexFunc = [defaultLibrary newFunctionWithName:[NSString stringWithUTF8String:vertexShader.c_str()]];
    id <MTLFunction> fragmentFunc = [defaultLibrary newFunctionWithName:[NSString stringWithUTF8String:fragmentShader.c_str()]];
    
    MTLRenderPipelineDescriptor * piplineDesc = [MTLRenderPipelineDescriptor new];
    piplineDesc.vertexFunction = vertexFunc;
    piplineDesc.fragmentFunction = fragmentFunc;
    piplineDesc.colorAttachments[0].pixelFormat = renderContextProvider.colorPixelFormat;
    piplineDesc.depthAttachmentPixelFormat = renderContextProvider.depthStencilPixelFormat;
    piplineDesc.stencilAttachmentPixelFormat = renderContextProvider.depthStencilPixelFormat;
    piplineDesc.sampleCount = renderContextProvider.sampleCount;
    
    NSError *error;
    id<MTLRenderPipelineState> pipelineState = [device newRenderPipelineStateWithDescriptor:piplineDesc error:&error];
    if (error) {
        NSLog(@"Create Pipline Failed. %@", error);
    }
    
    [NSObjectHolder retain: pipelineState];
    piplineStateSet(this, (__bridge void *)pipelineState);
    
    return selv;
}

ELRenderPipline::~ELRenderPipline() {
    id<MTLRenderPipelineState> pipelineState = (__bridge id<MTLRenderPipelineState>)piplineStateGet(this);
    ELRelease(pipelineState);
}

ELInt ELRenderPipline::getUniformLocation(std::string uniformName) {
    for (auto iter = uniformBuffer->attributes.begin(); iter != uniformBuffer->attributes.end(); ++iter) {
        if (iter->name == uniformName) {
            return (ELInt)(iter - uniformBuffer->attributes.begin());
        }
    }
    return -1;
}

void ELRenderPipline::setUniform(ELInt val, ELInt location) {}
void ELRenderPipline::setUniform(ELFloat val, ELInt location) {}
void ELRenderPipline::setUniform(ELVector2 val, ELInt location) {}
void ELRenderPipline::setUniform(ELVector3 val, ELInt location) {}
void ELRenderPipline::setUniform(ELVector4 val, ELInt location) {}
void ELRenderPipline::setUniform(ELMatrix2 val, ELInt location) {}
void ELRenderPipline::setUniform(ELMatrix3 val, ELInt location) {}
void ELRenderPipline::setUniform(ELMatrix4 val, ELInt location) {
    ELInt offset = uniformBuffer->attributes[location].offsetInBytes;
    memcpy((void *)((unsigned char *)uniformBuffer->data() + offset), (void *)&val, sizeof(ELMatrix4));
    uniformBuffer->flushBuffer();
}

void ELRenderPipline::bindTexture(ELTexturePtr texture, ELInt uniformLocation) {}

void ELRenderPipline::clearState() {
    
}
