//
// Created by wang yang on 2017/8/7.
//

#include "renderer/ELLambertBlinnDecalRenderer.h"
#include "platform/ELPlatform.h"

void ELLambertBlinnDecalRenderer::initPipline() {
    std::string vertexShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("vtx_base.glsl"));
    std::string fragmentShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("frag_lambert_blinn_decal.glsl"));
    pipline = ELRenderPipline::alloc()->init(vertexShader, fragmentShader);
}
