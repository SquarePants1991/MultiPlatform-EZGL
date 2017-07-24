//
// Created by wang yang on 2017/7/24.
//

#include "renderer/ELLambertPhongRenderer.h"
#include "platform/ELPlatform.h"

void ELLambertPhongRenderer::initPipline() {
    std::string vertexShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("vtx_base.glsl"));
    std::string fragmentShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("frag_lambert_phong.glsl"));
    pipline = ELRenderPipline::alloc()->init(vertexShader, fragmentShader);
}