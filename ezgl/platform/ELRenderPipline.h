//
// Created by wangyang on 2017/5/23.
//

#ifndef EZGL_ELRENDERPIPLINE_H
#define EZGL_ELRENDERPIPLINE_H

#include "types/EZGLTypes.h"

#include "ELCppBase.h"
#include "ELCrossPlatformObject.h"
#include "ELTexture.h"

classDefExt(ELRenderPipline, ELCrossPlatformObject)

public:
    ELRenderPiplinePtr init(std::string vertexShader, std::string fragmentShader);

    void setUniform(ELInt val, ELInt location);
    void setUniform(ELFloat val, ELInt location);
    void setUniform(ELVector2 val, ELInt location);
    void setUniform(ELVector3 val, ELInt location);
    void setUniform(ELVector4 val, ELInt location);
    void setUniform(ELMatrix2 val, ELInt location);
    void setUniform(ELMatrix3 val, ELInt location);
    void setUniform(ELMatrix4 val, ELInt location);

    void bindTexture(ELTexturePtr texture, ELInt location);

defEnd


#endif //EZGL_ELRENDERPIPLINE_H
