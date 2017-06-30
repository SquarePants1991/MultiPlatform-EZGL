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

void setupDepthStencil(ELRendererPtr renderer) {
    id <MTLDevice> device = ELMetalAdapter::defaultAdapter()->metalDevice;
    id <MTLRenderCommandEncoder> encoder = (__bridge id <MTLRenderCommandEncoder> )renderer->__crossplatformFetchObject("currentCommandEncoder");
    if (!encoder) {
        return;
    }
    static MTLCompareFunction compareFunc[] = {
        MTLCompareFunctionNever,
        MTLCompareFunctionAlways,
        MTLCompareFunctionLess,
        MTLCompareFunctionGreater,
        MTLCompareFunctionEqual,
        MTLCompareFunctionLessEqual,
        MTLCompareFunctionGreaterEqual,
        MTLCompareFunctionNotEqual,
    };
    if (renderer->isDepthTestEnabled) {
        MTLDepthStencilDescriptor *depthStencilDescriptor = [MTLDepthStencilDescriptor new];
        depthStencilDescriptor.depthCompareFunction = compareFunc[renderer->depthFunc];
        depthStencilDescriptor.depthWriteEnabled = renderer->isDepthWriteEnabled;
        
        if (renderer->isStencilTestEnabled) {
            MTLStencilDescriptor *stencilDescriptor = [MTLStencilDescriptor new];
            stencilDescriptor.readMask = renderer->stencilFuncArgs.mask;
            stencilDescriptor.writeMask = renderer->stencilMask;
            static MTLStencilOperation stencilOps[] = {
                MTLStencilOperationKeep,
                MTLStencilOperationZero,
                MTLStencilOperationIncrementClamp,
                MTLStencilOperationIncrementWrap,
                MTLStencilOperationDecrementClamp,
                MTLStencilOperationDecrementWrap,
                MTLStencilOperationInvert,
                MTLStencilOperationReplace,
            };
            stencilDescriptor.stencilCompareFunction = compareFunc[renderer->stencilFuncArgs.testType];
            stencilDescriptor.depthFailureOperation = stencilOps[renderer->stencilOpArgs.depthTestFailed];
            stencilDescriptor.stencilFailureOperation = stencilOps[renderer->stencilOpArgs.stencilTestFailed];
            stencilDescriptor.depthStencilPassOperation = stencilOps[renderer->stencilOpArgs.success];
            depthStencilDescriptor.frontFaceStencil = stencilDescriptor;
            depthStencilDescriptor.backFaceStencil = stencilDescriptor;
            [encoder setStencilReferenceValue:renderer->stencilFuncArgs.ref];
        }
        id<MTLDepthStencilState> depthStencilState = [device newDepthStencilStateWithDescriptor: depthStencilDescriptor];
        [encoder setDepthStencilState:depthStencilState];
    }
}

ELRendererPtr ELRenderer::init(ELRenderPassPtr renderPass, ELRenderPiplinePtr pipline) {
    selv->renderPass = renderPass;
    selv->pipline = pipline;
    id <MTLCommandQueue> commandQueue = [ELMetalAdapter::defaultAdapter()->metalDevice newCommandQueue];
    [NSObjectHolder retain: commandQueue];
    commandQueueSet(this, (__bridge void *)commandQueue);
    
    // init blend vars
    selv->isBlendEnabled = false;
    selv->srcBlendFactor = ELBlendFactorUndef;
    selv->dstBlendFactor = ELBlendFactorUndef;
    // init depth test vars
    selv->isDepthTestEnabled = false;
    selv->depthFunc = ELTestLessEqual;
    // init depth mask vars
    selv->isDepthWriteEnabled = false;
    // init stencil mask vars
    selv->isStencilTestEnabled = false;
    selv->stencilMask = 0xff;
    selv->stencilOpArgs = ELStencilOpArgsMake(ELStencilOpKeep, ELStencilOpKeep, ELStencilOpReplace);
    selv->stencilFuncArgs = ELStencilFuncArgsMake(ELTestAlways, 0, 0xFF);
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
    
    descriptor.colorAttachments[0].blendingEnabled = selv->isBlendEnabled;
    if (selv->isBlendEnabled) {
        static MTLBlendFactor blendFactors[] = {
            MTLBlendFactorOne,
            MTLBlendFactorZero,
            MTLBlendFactorSourceAlpha,
            MTLBlendFactorSourceColor,
            MTLBlendFactorDestinationAlpha,
            MTLBlendFactorDestinationColor,
            MTLBlendFactorOneMinusSourceAlpha,
            MTLBlendFactorOneMinusSourceColor,
            MTLBlendFactorOneMinusDestinationAlpha,
            MTLBlendFactorOneMinusDestinationColor,
        };
        descriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
        descriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
        descriptor.colorAttachments[0].sourceRGBBlendFactor = blendFactors[selv->srcBlendFactor];
        descriptor.colorAttachments[0].destinationRGBBlendFactor = blendFactors[selv->dstBlendFactor];
        descriptor.colorAttachments[0].sourceAlphaBlendFactor = blendFactors[selv->srcBlendFactor];
        descriptor.colorAttachments[0].destinationAlphaBlendFactor = blendFactors[selv->dstBlendFactor];
    }
    
    id <MTLRenderPipelineState> piplineState = [device newRenderPipelineStateWithDescriptor:descriptor error:nil];
    
    id <MTLRenderCommandEncoder> encoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
    [encoder setRenderPipelineState:piplineState];
    
    currentCommandEncoderSet(this, (__bridge void *)encoder);
    currentCommandBufferSet(this, (__bridge void *)commandBuffer);
    setupDepthStencil(selv);
    
    [NSObjectHolder retain: commandBuffer];
    [NSObjectHolder retain: encoder];
}

void ELRenderer::drawPrimitives(ELPrimitivesType type, ELVertexBufferPtr vertexBuffer) {
    id <MTLBuffer> mtlBuffer = (__bridge id <MTLBuffer>)vertexBuffer->__crossplatformFetchObject("vertexBuffer");
    id <MTLBuffer> mtlIndexBuffer = (__bridge id <MTLBuffer>)vertexBuffer->__crossplatformFetchObject("indexBuffer");
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
    
    
    static MTLPrimitiveType primitiveTypeMap[] = {
        MTLPrimitiveTypeTriangle,
        MTLPrimitiveTypeTriangleStrip,
        MTLPrimitiveTypeLine,
        MTLPrimitiveTypeLineStrip,
        MTLPrimitiveTypePoint,
    };
    if (vertexBuffer->useIndex) {
        [encoder drawIndexedPrimitives:primitiveTypeMap[type] indexCount:vertexBuffer->vertexCount() indexType: MTLIndexTypeUInt32 indexBuffer:mtlIndexBuffer indexBufferOffset:0];
    } else {
        [encoder drawPrimitives:primitiveTypeMap[type] vertexStart:0 vertexCount:vertexBuffer->vertexCount()];
    }
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

void ELRenderer::enableBlend() {
    selv->isBlendEnabled = true;
}
void ELRenderer::disableBlend() {
    selv->isBlendEnabled = false;
}
void ELRenderer::setBlendMode(ELBlendFactor srcFactor, ELBlendFactor dstFactor) {
    selv->srcBlendFactor = srcFactor;
    selv->dstBlendFactor = dstFactor;
}

void ELRenderer::enableDepthTest() {
    selv->isDepthTestEnabled = true;
    selv->isDepthWriteEnabled = true;
    selv->depthFunc = ELTestLess;
    setupDepthStencil(selv);
}
void ELRenderer::disableDepthTest() {
    selv->isDepthTestEnabled = false;
    selv->isDepthWriteEnabled = false;
    setupDepthStencil(selv);
}
void ELRenderer::setDepthFunc(ELTest testType) {
    selv->depthFunc = testType;
    setupDepthStencil(selv);
}

void ELRenderer::enableDepthWrite() {
    selv->isDepthWriteEnabled = true;
    setupDepthStencil(selv);
}
void ELRenderer::disableDepthWrite() {
    selv->isDepthWriteEnabled = false;
    setupDepthStencil(selv);
}

void ELRenderer::enableStencilTest() {
    selv->isStencilTestEnabled = true;
    setupDepthStencil(selv);
}

void ELRenderer::disableStencilTest() {
    selv->isStencilTestEnabled = false;
    setupDepthStencil(selv);
}

void ELRenderer::setStencilFunc(ELTest testType, ELInt ref, ELInt mask) {
    selv->stencilFuncArgs = ELStencilFuncArgsMake(testType, ref, mask);
    setupDepthStencil(selv);
}

void ELRenderer::setStencilOperations(ELStencilOp stFailed, ELStencilOp dpFailed, ELStencilOp allSuccess) {
    selv->stencilOpArgs = ELStencilOpArgsMake(stFailed, dpFailed, allSuccess);
    setupDepthStencil(selv);
}

void ELRenderer::setStencilMask(ELInt mask) {
    selv->stencilMask = mask;
    setupDepthStencil(selv);
}


