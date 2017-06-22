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

enum ELTest {
    ELTestNone = -1,
    ELTestNever = 0,
    ELTestAlways,
    ELTestLess,
    ELTestGreater,
    ELTestEqual,
    ELTestLessEqual,
    ELTestGreaterEqual,
    ELTestNotEqual,
};

enum ELStencilOp {
    ELStencilOpNone = -1,
    ELStencilOpKeep = 0,
    ELStencilOpZero,
    ELStencilOpIncrement,
    ELStencilOpIncrementWrap,
    ELStencilOpDecrement,
    ELStencilOpDecrementWrap,
    ELStencilOpInvert,
    ELStencilOpReplace,
};

typedef struct {
    ELTest testType;
    ELInt ref;
    ELInt mask;
} ELStencilFuncArgs;

static inline ELStencilFuncArgs ELStencilFuncArgsMake(ELTest testType, ELInt ref, ELInt mask) {
    ELStencilFuncArgs arg;
    arg.testType = testType;
    arg.ref = ref;
    arg.mask = mask;
    return arg;
}

static inline bool ELStencilFuncArgsEqual(ELStencilFuncArgs left, ELStencilFuncArgs right) {
    return left.mask == right.mask && left.ref == right.ref && left.testType == right.testType;
}

typedef struct {
    ELStencilOp stencilTestFailed;
    ELStencilOp depthTestFailed;
    ELStencilOp success;
} ELStencilOpArgs;

static inline ELStencilOpArgs ELStencilOpArgsMake(ELStencilOp stencilTestFailed, ELStencilOp depthTestFailed, ELStencilOp success) {
    ELStencilOpArgs arg;
    arg.stencilTestFailed = stencilTestFailed;
    arg.depthTestFailed = depthTestFailed;
    arg.success = success;
    return arg;
}

static inline bool ELStencilOpArgsEqual(ELStencilOpArgs left, ELStencilOpArgs right) {
    return left.stencilTestFailed == right.stencilTestFailed && left.depthTestFailed == right.depthTestFailed && left.success == right.success;
}

classDefExt(ELRenderer, public ELCrossPlatformObject)

public:
    ELRendererPtr init(ELRenderPassPtr renderPass, ELRenderPiplinePtr pipline);

    void prepare();
    void drawPrimitives(ELPrimitivesType type, ELVertexBufferPtr vertexBuffer);
    void drawPrimitives(ELPrimitivesType type, ELCompositionVertexBufferPtr vertexBuffer);
    void endRender();

    void enableBlend();
    void disableBlend();
    void setBlendMode(ELBlendFactor srcFactor, ELBlendFactor dstFactor);

    void enableDepthTest();
    void disableDepthTest();
    void setDepthFunc(ELTest testType);

    void enableDepthWrite();
    void disableDepthWrite();

    void enableStencilTest();
    void disableStencilTest();
    void setStencilFunc(ELTest testType, ELInt ref, ELInt mask);
    void setStencilOperations(ELStencilOp stFailed, ELStencilOp dpFailed, ELStencilOp allSuccess);
    void setStencilMask(ELInt mask);


public:
    ELRenderPassPtr renderPass;
    ELRenderPiplinePtr pipline;
    // Blend Mode
    bool isBlendEnabled;
    ELBlendFactor srcBlendFactor;
    ELBlendFactor dstBlendFactor;
    // Depth Test
    bool isDepthTestEnabled;
    ELTest depthFunc;
    // Depth Write
    bool isDepthWriteEnabled;
    // Stencil Test
    bool isStencilTestEnabled;
    ELInt stencilMask;
    ELStencilFuncArgs stencilFuncArgs;
    ELStencilOpArgs stencilOpArgs;

defEnd


#endif //EZGL_ELRENDERER_H
