//
// Created by wang yang on 2017/8/2.
//

#include "renderer/ELLambertBlinnRenderer.h"
#include "platform/ELPlatform.h"

void ELLambertBlinnRenderer::initPipline() {
    std::string vertexShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("vtx_base.glsl"));
    std::string fragmentShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("frag_lambert_blinn.glsl"));
    pipline = ELRenderPipline::alloc()->init(vertexShader, fragmentShader);
}