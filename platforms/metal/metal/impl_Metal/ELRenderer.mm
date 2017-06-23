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
    id <MTLDrawable> drawable = nil;
    MTLRenderPassDescriptor *renderPassDescriptor = nil;
    if (renderPass->renderTarget->__crossplatformFetchBool("isDefaultTarget")) {
        drawable = ELMetalAdapter::defaultAdapter()->renderContextProvider.currentDrawable;
        renderPassDescriptor = ELMetalAdapter::defaultAdapter()->renderContextProvider.currentRenderPassDescriptor;
        renderPassDescriptor.colorAttachments[0].loadAction = (MTLLoadAction)renderPass->config.loadAction;
        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(renderPass->config.clearColor.x, renderPass->config.clearColor.y, renderPass->config.clearColor.z, renderPass->config.clearColor.w);
        renderPassDescriptor.depthAttachment.loadAction = (MTLLoadAction)renderPass->config.loadAction;
        renderPassDescriptor.depthAttachment.clearDepth = 1.0;
    }
    
    id <MTLCommandQueue> commandQueue = (__bridge id <MTLCommandQueue>)commandQueueGet(this);
    id <MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
    
    id <MTLRenderPipelineState> piplineState = (__bridge id <MTLRenderPipelineState>)pipline->__crossplatformFetchObject("piplineState");
    
    id <MTLRenderCommandEncoder> encoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
    [encoder setRenderPipelineState:piplineState];
    
    currentCommandEncoderSet(this, (__bridge void *)encoder);
    currentCommandBufferSet(this, (__bridge void *)commandBuffer);
    
    [NSObjectHolder retain: commandBuffer];
    [NSObjectHolder retain: encoder];
}

void ELRenderer::drawPrimitives(ELPrimitivesType type, ELVertexBufferPtr vertexBuffer) {
    id <MTLBuffer> mtlBuffer = (__bridge id <MTLBuffer>)vertexBuffer->__crossplatformFetchObject("vertexBuffer");
    id <MTLRenderCommandEncoder> encoder = (__bridge id <MTLRenderCommandEncoder> )currentCommandEncoderGet(this);
    id <MTLBuffer> uniformBuffer = (__bridge id <MTLBuffer> )pipline->uniformBuffer->__crossplatformFetchObject("vertexBuffer");
    
    [encoder setVertexBuffer:mtlBuffer offset:0 atIndex:0];
    [encoder setVertexBuffer:uniformBuffer offset:0 atIndex:1];
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
    
    [commandBuffer presentDrawable:drawable];
    [commandBuffer commit];
    
    [NSObjectHolder release: commandBuffer];
    [NSObjectHolder release: encoder];
}

void ELRenderer::enableBlend() {}
void ELRenderer::disableBlend() {}
void ELRenderer::setBlendMode(ELBlendFactor srcFactor, ELBlendFactor dstFactor) {}

void ELRenderer::enableDepthTest() {}
void ELRenderer::disableDepthTest() {}
void ELRenderer::setDepthFunc(ELTest testType) {}

void ELRenderer::enableDepthWrite() {}
void ELRenderer::disableDepthWrite() {}

void ELRenderer::enableStencilTest() {}
void ELRenderer::disableStencilTest() {}
void ELRenderer::setStencilFunc(ELTest testType, ELInt ref, ELInt mask) {}
void ELRenderer::setStencilOperations(ELStencilOp stFailed, ELStencilOp dpFailed, ELStencilOp allSuccess) {}
void ELRenderer::setStencilMask(ELInt mask) {}
