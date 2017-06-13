//
// Created by wangyang on 2017/5/23.
//

#ifndef EZGL_ELRENDERER_H
#define EZGL_ELRENDERER_H

#include "ELCppBase.h"
#include "ELCrossPlatformObject.h"
#include "types/EZGLTypes.h"
#include "ELRenderPass.h"
#include "ELVertexBuffer.h"
#include "ELCompositionVertexBuffer.h"
#include "ELRenderPipline.h"

enum ELPrimitivesType {
    ELPrimitivesTypeTriangle,
    ELPrimitivesTypeTriangleStrip,
    ELPrimitivesTypeLine,
    ELPrimitivesTypeLineStrip,
    ELPrimitivesTypePoint,
};

enum ELBlendFactor {
    ELBlendFactorUndef = -1,
    ELBlendFactorOne = 0,
    ELBlendFactorZero,
    ELBlendFactorSrcAlpha,
    ELBlendFactorSrcColor,
    ELBlendFactorDstAlpha,
    ELBlendFactorDstColor,
    ELBlendFactorOneMinusSrcAlpha,
    ELBlendFactorOneMinusSrcColor,
    ELBlendFactorOneMinusDstAlpha,
    ELBlendFactorOneMinusDstColor,
};

classDefExt(ELRenderer, ELCrossPlatformObject)

public:
    ELRendererPtr init(ELRenderPassPtr renderPass, ELRenderPiplinePtr pipline);

    void prepare();
    void drawPrimitives(ELPrimitivesType type, ELVertexBufferPtr vertexBuffer);
    void drawPrimitives(ELPrimitivesType type, ELCompositionVertexBufferPtr vertexBuffer);
    void endRender();

    void enableBlend();
    void disableBlend();
    void setBlendMode(ELBlendFactor srcFactor, ELBlendFactor dstFactor);

public:
    ELRenderPassPtr renderPass;
    ELRenderPiplinePtr pipline;
    // Blend Mode
    bool isBlendEnabled;
    ELBlendFactor srcBlendFactor;
    ELBlendFactor dstBlendFactor;

defEnd


#endif //EZGL_ELRENDERER_H
