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
        
    } else {
        // create form texture
    }
    return selv;
}

