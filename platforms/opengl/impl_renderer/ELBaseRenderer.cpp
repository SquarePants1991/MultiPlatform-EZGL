//
// Created by wang yang on 2017/7/4.
//

#include "renderer/ELBaseRenderer.h"
#include "platform/ELPlatform.h"

void ELBaseRenderer::initPipline() {
    std::string vertexShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("vtx_base.glsl"));
    std::string fragmentShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("frg_base.glsl"));
    pipline = ELRenderPipline::alloc()->init(vertexShader, fragmentShader);
}