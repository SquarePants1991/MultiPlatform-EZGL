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

classDefExt(ELRenderer, ELCrossPlatformObject)

public:
    ELRendererPtr init(ELRenderPassPtr renderPass, ELRenderPiplinePtr pipline);

    void prepare();
    void drawPrimitives(ELPrimitivesType type, ELVertexBufferPtr vertexBuffer);
    void drawPrimitives(ELPrimitivesType type, ELCompositionVertexBufferPtr vertexBuffer);
    void drawIndexedPrimitives(ELPrimitivesType type, ELVertexBufferPtr vertexBuffer, ELVertexBufferPtr indexBuffer);
    void endRender();

public:
    ELRenderPassPtr renderPass;
    ELRenderPiplinePtr pipline;

defEnd


#endif //EZGL_ELRENDERER_H
