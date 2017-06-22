//
// Created by wangyang on 2017/5/24.
//

#include "../ELRenderPass.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../types/EZGLTypes.h"

ELRenderPassPtr ELRenderPass::init(ELRenderPassConfig config, ELRenderTargetPtr renderTarget) {
    selv->config = config;
    selv->renderTarget = renderTarget;
    return selv;
}

