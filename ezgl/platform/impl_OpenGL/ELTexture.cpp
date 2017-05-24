//
// Created by wangyang on 2017/5/24.
//

#include "../ELTexture.h"

crossplatform_var(ELInt, glVal)

ELTexturePtr ELTexture::init(ELPixelFormat pixelFormat, char *imageData, ELInt dataLength) {
    glValSet(this, -1);
}