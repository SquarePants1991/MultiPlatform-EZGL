//
// Created by wangyang on 2017/5/23.
//

#ifndef EZGL_ELRENDERER_H
#define EZGL_ELRENDERER_H

#include "ELCppBase.h"
#include "ELCrossPlatformObject.h"
#include "types/EZGLTypes.h"
#include "ELRenderPass.h"

classDefExt(ELRenderer, ELCrossPlatformObject)

public:
    ELRendererPtr init(ELRenderPassPtr renderPass);

    void setVertexBuffer();
    void drawPrimitives();
defEnd


#endif //EZGL_ELRENDERER_H
