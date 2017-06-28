//
// Created by wangyang on 2017/5/24.
//

#include "platform/ELRenderer.h"
#include "platform/types/EZGLTypes.h"
#include "platform/ELPlatform.h"
#include "platform/ELRenderPass.h"
#import "ELMetalAdapter.h"
#import "NSObjectHolder.h"

crossplatform_var_obj(commandQueue)
crossplatform_var_obj(currentCommandEncoder)
crossplatform_var_obj(currentCommandBuffer)

ELRendererPtr ELRenderer::init(ELRenderPassPtr renderPass, ELRenderPiplinePtr pipline) {
    selv->renderPass = renderPass;
    selv->pipline = pipline;
    id <MTLCommandQueue> commandQueue = [ELMetalAdapter::defaultAdapter()->metalDevice newCommandQueue];
    [NSObjectHolder retain: commandQueue];
    commandQueueSet(this, (__bridge void *)commandQueue);
    return selv;
}

void ELRenderer::prepare() {
    pipline->clearState();
    
    id <MTLDrawable> drawable = nil;
    MTLRenderPassDescriptor *renderPassDescriptor = nil;
    if (renderPass->renderTarget->__crossplatformFetchBool("isDefaultTarget")) {
        drawable = ELMetalAdapter::defaultAdapter()->renderContextProvider.currentDrawable;
        renderPassDescriptor = ELMetalAdapter::defaultAdapter()->renderContextProvider.currentRenderPassDescriptor;
    } else {
        renderPassDescriptor = (__bridge MTLRenderPassDescriptor *)(renderPass->__crossplatformFetchObject("renderPassDescriptor"));
    }
    renderPassDescriptor.colorAttachments[0].loadAction = (MTLLoadAction)renderPass->config.loadAction;
    renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(renderPass->config.clearColor.x, renderPass->config.clearColor.y, renderPass->config.clearColor.z, renderPass->config.clearColor.w);
    renderPassDescriptor.depthAttachment.loadAction = (MTLLoadAction)renderPass->config.loadAction;
    renderPassDescriptor.depthAttachment.storeAction = MTLStoreActionStore;
    renderPassDescriptor.depthAttachment.clearDepth = 1.0;
    
    if (renderPassDescriptor == nil) {
        return;
    }
    
    id <MTLDevice> device = ELMetalAdapter::defaultAdapter()->metalDevice;
    id <MTLCommandQueue> commandQueue = (__bridge id <MTLCommandQueue>)commandQueueGet(this);
    id <MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
    
    MTLRenderPipelineDescriptor *descriptor = (__bridge MTLRenderPipelineDescriptor *)pipline->__crossplatformFetchObject("piplineDescriptor");
    if (renderPassDescriptor.colorAttachments[0].texture) {
        descriptor.colorAttachments[0].pixelFormat = renderPassDescriptor.colorAttachments[0].texture.pixelFormat;
    } else {
        descriptor.colorAttachments[0].pixelFormat = MTLPixelFormatInvalid;
    }
    if (renderPassDescriptor.depthAttachment.texture) {
        descriptor.depthAttachmentPixelFormat = renderPassDescriptor.depthAttachment.texture.pixelFormat;
    } else {
        descriptor.depthAttachmentPixelFormat = MTLPixelFormatInvalid;
    }
    
    if (renderPassDescriptor.stencilAttachment.texture) {
        descriptor.stencilAttachmentPixelFormat = renderPassDescriptor.stencilAttachment.texture.pixelFormat;
    } else {
        descriptor.stencilAttachmentPixelFormat = MTLPixelFormatInvalid;
    }
    
    id <MTLRenderPipelineState> piplineState = [device newRenderPipelineStateWithDescriptor:descriptor error:nil];
    
    id <MTLRenderCommandEncoder> encoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
    [encoder setRenderPipelineState:piplineState];
    
    if (selv->isDepthTestEnabled) {
        static MTLCompareFunction depthTestFuncs[] = {
            MTLCompareFunctionNever,
            MTLCompareFunctionAlways,
            MTLCompareFunctionLess,
            MTLCompareFunctionGreater,
            MTLCompareFunctionEqual,
            MTLCompareFunctionLessEqual,
            MTLCompareFunctionGreaterEqual,
            MTLCompareFunctionNotEqual,
        };
        MTLDepthStencilDescriptor *depthStencilDescriptor = [MTLDepthStencilDescriptor new];
        depthStencilDescriptor.depthCompareFunction = depthTestFuncs[selv->depthFunc];
        depthStencilDescriptor.depthWriteEnabled = selv->isDepthWriteEnabled;
        
        id<MTLDepthStencilState> depthStencilState = [device newDepthStencilStateWithDescriptor: depthStencilDescriptor];
        [encoder setDepthStencilState:depthStencilState];
    }
    
    
    currentCommandEncoderSet(this, (__bridge void *)encoder);
    currentCommandBufferSet(this, (__bridge void *)commandBuffer);
    
    [NSObjectHolder retain: commandBuffer];
    [NSObjectHolder retain: encoder];
}

void ELRenderer::drawPrimitives(ELPrimitivesType type, ELVertexBufferPtr vertexBuffer) {
    id <MTLBuffer> mtlBuffer = (__bridge id <MTLBuffer>)vertexBuffer->__crossplatformFetchObject("vertexBuffer");
    id <MTLRenderCommandEncoder> encoder = (__bridge id <MTLRenderCommandEncoder> )currentCommandEncoderGet(this);
    id <MTLBuffer> uniformBuffer = (__bridge id <MTLBuffer> )pipline->uniformBuffer->__crossplatformFetchObject("vertexBuffer");
    
    if (encoder == nil) {
        return;
    }
    [encoder setVertexBuffer:mtlBuffer offset:0 atIndex:0];
    [encoder setVertexBuffer:uniformBuffer offset:0 atIndex:1];
    for (auto iter = pipline->textures.begin(); iter != pipline->textures.end(); ++iter) {
        if (*iter && (*iter)->__crossplatformObjectExist("mtlTexture")) {
            id <MTLTexture> mtlTexture = (__bridge id <MTLTexture> )((*iter)->__crossplatformFetchObject("mtlTexture"));
            [encoder setFragmentTexture:mtlTexture atIndex:(int)(iter - pipline->textures.begin())];
        }
    }
    [encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:vertexBuffer->vertexCount()];
}

void ELRenderer::drawPrimitives(ELPrimitivesType type, ELCompositionVertexBufferPtr vertexBuffer) {}

void ELRenderer::endRender() {
    id <MTLDrawable> drawable = nil;
    if (renderPass->renderTarget->__crossplatformFetchBool("isDefaultTarget")) {
        drawable = ELMetalAdapter::defaultAdapter()->renderContextProvider.currentDrawable;
    } else {
        // May be Draw to texture
    }
    id <MTLCommandBuffer> commandBuffer = (__bridge id <MTLCommandBuffer> )currentCommandBufferGet(this);
    id <MTLRenderCommandEncoder> encoder = (__bridge id <MTLRenderCommandEncoder> )currentCommandEncoderGet(this);
    
    [encoder endEncoding];
    if (drawable) {
        [commandBuffer presentDrawable:drawable];
    }
    [commandBuffer commit];
    
    [NSObjectHolder release: commandBuffer];
    [NSObjectHolder release: encoder];
}

void ELRenderer::enableBlend() {}
void ELRenderer::disableBlend() {}
void ELRenderer::setBlendMode(ELBlendFactor srcFactor, ELBlendFactor dstFactor) {}

void ELRenderer::enableDepthTest() {
    selv->isDepthTestEnabled = true;
    selv->isDepthWriteEnabled = true;
    selv->depthFunc = ELTestLess;
}
void ELRenderer::disableDepthTest() {}
void ELRenderer::setDepthFunc(ELTest testType) {}

void ELRenderer::enableDepthWrite() {}
void ELRenderer::disableDepthWrite() {}

void ELRenderer::enableStencilTest() {}
void ELRenderer::disableStencilTest() {}
void ELRenderer::setStencilFunc(ELTest testType, ELInt ref, ELInt mask) {}
void ELRenderer::setStencilOperations(ELStencilOp stFailed, ELStencilOp dpFailed, ELStencilOp allSuccess) {}
void ELRenderer::setStencilMask(ELInt mask) {}


