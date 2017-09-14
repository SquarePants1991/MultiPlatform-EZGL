//
// Created by wang yang on 2017/9/14.
//

#include "renderer/ELSkyBoxRenderer.h"
#include "platform/ELPlatform.h"

void ELSkyBoxRenderer::initPipline() {
    std::string vertexShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("vtx_base.glsl"));
    std::string fragmentShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("frag_skybox.glsl"));
    pipline = ELRenderPipline::alloc()->init(vertexShader, fragmentShader);
}