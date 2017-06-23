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
    
    if (renderTarget->__crossplatformObjectExist("defaultRenderPassDesc")) {
        MTLRenderPassDescriptor *renderPassDescriptor = (__bridge MTLRenderPassDescriptor *)renderTarget->__crossplatformFetchObject("defaultRenderPassDesc");
        renderPassDescriptor.colorAttachments[0].loadAction = (MTLLoadAction)config.loadAction;
        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(config.clearColor.x, config.clearColor.y, config.clearColor.z, config.clearColor.w);
        renderPassDescriptorSet(this, (__bridge void *)renderPassDescriptor);
        [NSObjectHolder retain: renderPassDescriptor];
    } else {
        // create form texture
    }
    return selv;
}

