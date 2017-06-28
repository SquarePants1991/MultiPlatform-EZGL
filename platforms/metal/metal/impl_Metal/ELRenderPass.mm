//
// Created by wangyang on 2017/5/24.
//

#include "platform/ELRenderPass.h"
#include "platform/types/EZGLTypes.h"
#import "ELMetalAdapter.h"
#import "NSObjectHolder.h"

crossplatform_var_obj(renderPassDescriptor)

ELRenderPassPtr ELRenderPass::init(ELRenderPassConfig config, ELRenderTargetPtr renderTarget) {
    selv->config = config;
    selv->renderTarget = renderTarget;
    
    if (renderTarget->__crossplatformFetchBool("isDefaultTarget")) {
        // Do nothing when target is default
    } else {
        MTLRenderPassDescriptor *renderPassDescriptor = [MTLRenderPassDescriptor new];
        if (renderTarget->colorBufferEnabled) {
            id <MTLTexture> mtlTexture = (__bridge id <MTLTexture> )renderTarget->bindTexture->__crossplatformFetchObject("mtlTexture");
            renderPassDescriptor.colorAttachments[0].texture = mtlTexture;
        }
         if (renderTarget->depthBufferEnabled) {
             id <MTLTexture> mtlTexture = (__bridge id <MTLTexture> )renderTarget->bindDepthTexture->__crossplatformFetchObject("mtlTexture");
             renderPassDescriptor.depthAttachment.texture = mtlTexture;
             renderPassDescriptor.stencilAttachment.texture = mtlTexture;
         }
        
        renderPassDescriptorSet(this, (__bridge void *)renderPassDescriptor);
        ELRetain(renderPassDescriptor);
    }
    return selv;
}

ELRenderPass::~ELRenderPass() {
    MTLRenderPassDescriptor * renderPassDescriptor = (__bridge MTLRenderPassDescriptor *)renderPassDescriptorGet(this);
    if (renderPassDescriptor) {
        ELRelease(renderPassDescriptor);
    }
}

