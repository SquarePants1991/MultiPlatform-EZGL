//
// Created by wangyang on 2017/5/23.
//

#ifndef EZGL_ELRENDERTARGET_H
#define EZGL_ELRENDERTARGET_H

#include "types/EZGLTypes.h"

#include "ELCppBase.h"
#include "ELTexture.h"
#include "ELCrossPlatformObject.h"

classDefExt(ELRenderTarget, ELCrossPlatformObject)

public:
    ELPixelFormat pixelFormat;  // 颜色缓冲区像素格式
    ELVector2 size;             // 缓冲区尺寸
    ELTexturePtr bindTexture;   // 渲染到的纹理

    bool colorBufferEnabled;    // 是否启用颜色缓冲区
    bool depthBufferEnabled;    // 是否启用深度缓冲区
    bool stencilBufferEnabled;  // 是否启用Stencil缓冲区
    bool isBindTexture;         // 是否渲染到纹理

    ELRenderTargetPtr init(ELPixelFormat pixelFormat, ELVector2 size, bool bindTexture, bool enableDepthBuffer = true, bool enableStencilBuffer = true);
    static ELRenderTargetPtr defaultTarget();

defEnd


#endif //EZGL_ELRENDERTARGET_H
