//
// Created by wang yang on 2017/5/21.
//

#ifndef PROJECT_ELTEXTURE_H
#define PROJECT_ELTEXTURE_H

#include "ELCppBase.h"
#include "types/EZGLTypes.h"
#include "ELCrossPlatformObject.h"

enum ELTextureStoreType {
    ELTextureStoreTypeCPU = 1 << 0,
    ELTextureStoreTypeGPU = 1 << 1,
};
enum ELTextureChannelFormat {
    ELTextureChannelFormatUC,
};

classDefExt(ELTexture, public ELCrossPlatformObject)
public:
    ELInt width;
    ELInt height;
    unsigned char *imageData;
    ELTextureChannelFormat channelFormat;
    ELInt numberOfChannel;
    ELPixelFormat pixelFormat;
    ELTexturePtr init(ELPixelFormat pixelFormat, unsigned char *imageData, ELInt width, ELInt height, ELTextureStoreType storeType = ELTextureStoreTypeGPU);
    ELTexturePtr init(std::string imagePath, ELTextureStoreType storeType = ELTextureStoreTypeGPU, ELPixelFormat pixelFormat = ELPixelFormatRGBA);
    ~ELTexture();
defEnd


#endif //PROJECT_ELTEXTURE_H
