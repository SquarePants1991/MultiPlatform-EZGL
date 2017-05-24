//
// Created by wang yang on 2017/5/21.
//

#ifndef PROJECT_ELTEXTURE_H
#define PROJECT_ELTEXTURE_H

#include "ELCppBase.h"
#include "types/EZGLTypes.h"
#include "ELCrossPlatformObject.h"

classDefExt(ELTexture, public ELCrossPlatformObject)
public:
    ELTexturePtr init(ELPixelFormat pixelFormat, char *imageData, ELInt dataLength);
defEnd


#endif //PROJECT_ELTEXTURE_H
