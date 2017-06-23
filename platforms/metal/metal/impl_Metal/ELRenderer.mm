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
    id <MTLCommandQueue> commandQueue = (__bridge id <MTLCommandQueue>)commandQueueGet(this);
    id <MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
    MTLRenderPassDescriptor *renderPassDescriptor = (__bridge MTLRenderPassDescriptor *)renderPass->__crossplatformFetchObject("renderPassDescriptor");
    id <MTLRenderPipelineState> piplineState = (__bridge id <MTLRenderPipelineState>)pipline->__crossplatformFetchObject("piplineState");
    
    id <MTLRenderCommandEncoder> encoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
    encoder.label = @"encoder default";
    [encoder pushDebugGroup:@"begin draw"];
    [encoder setRenderPipelineState:piplineState];
    
    currentCommandEncoderSet(this, (__bridge void *)encoder);
    currentCommandBufferSet(this, (__bridge void *)commandBuffer);
    
    [NSObjectHolder retain: commandBuffer];
    [NSObjectHolder retain: encoder];
}

void ELRenderer::drawPrimitives(ELPrimitivesType type, ELVertexBufferPtr vertexBuffer) {}
void ELRenderer::drawPrimitives(ELPrimitivesType type, ELCompositionVertexBufferPtr vertexBuffer) {}
void ELRenderer::endRender() {
    id <MTLDrawable> drawable = (__bridge id <MTLDrawable>)renderPass->renderTarget->__crossplatformFetchObject("drawable");
    id <MTLCommandEncoder> encoder = (__bridge id <MTLRenderCommandEncoder> )currentCommandEncoderGet(this);
    id <MTLCommandBuffer> buffer = (__bridge id <MTLCommandBuffer> )currentCommandBufferGet(this);
    
    [encoder popDebugGroup];
    [encoder endEncoding];
    
    [buffer presentDrawable:drawable];
    [buffer commit];
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
