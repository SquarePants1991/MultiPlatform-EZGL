//
// Created by wangyang on 2017/5/23.
//

#ifndef EZGL_ELRENDERPIPLINE_H
#define EZGL_ELRENDERPIPLINE_H

#include "types/EZGLTypes.h"

#include "ELCppBase.h"
#include "ELCrossPlatformObject.h"
#include "ELTexture.h"
#include "ELVertexBuffer.h"

classDefExt(ELRenderPipline, public ELCrossPlatformObject)

public:
    ELRenderPiplinePtr init(std::string vertexShader, std::string fragmentShader);
    ~ELRenderPipline();

    ELInt getUniformLocation(std::string uniformName);
    void setUniform(ELInt val, ELInt location);
    void setUniform(ELFloat val, ELInt location);
    void setUniform(ELVector2 val, ELInt location);
    void setUniform(ELVector3 val, ELInt location);
    void setUniform(ELVector4 val, ELInt location);
    void setUniform(ELMatrix2 val, ELInt location);
    void setUniform(ELMatrix3 val, ELInt location);
    void setUniform(ELMatrix4 val, ELInt location);
    void bindTexture(ELTexturePtr texture, ELInt uniformLocation);

    // 目前主要清空纹理计数，清理上一次可能遗留的状态数据
    void clearState();
    // Metal will use this buffer to setup uniform structure
    ELVertexBufferPtr uniformBuffer;
defEnd


#endif //EZGL_ELRENDERPIPLINE_H
