//
// Created by wangyang on 2017/5/23.
//

#ifndef EZGL_ELRENDERPIPLINE_H
#define EZGL_ELRENDERPIPLINE_H

#include "types/EZGLTypes.h"

#include "ELCppBase.h"
#include "ELCrossPlatformObject.h"
#include "ELTexture.h"

classDefExt(ELRenderPipline, public ELCrossPlatformObject)

public:
    ELRenderPiplinePtr init(std::string vertexShader, std::string fragmentShader);
    ~ELRenderPipline();

    inline ELInt getUniformLocation(std::string uniformName);
    inline void setUniform(ELInt val, ELInt location);
    inline void setUniform(ELFloat val, ELInt location);
    inline void setUniform(ELVector2 val, ELInt location);
    inline void setUniform(ELVector3 val, ELInt location);
    inline void setUniform(ELVector4 val, ELInt location);
    inline void setUniform(ELMatrix2 val, ELInt location);
    inline void setUniform(ELMatrix3 val, ELInt location);
    inline void setUniform(ELMatrix4 val, ELInt location);

    inline void bindTexture(ELTexturePtr texture, ELInt uniformLocation, ELInt textureID);

defEnd


#endif //EZGL_ELRENDERPIPLINE_H
