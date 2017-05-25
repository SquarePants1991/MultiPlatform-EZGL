//
// Created by wangyang on 2017/5/24.
//

#include "../ELTexture.h"
#include "soil/SOIL.h"
#include <GL/glew.h>

crossplatform_var_int(glVal)

ELTexturePtr ELTexture::init(std::string imagePath, ELTextureStoreType storeType, ELPixelFormat pixelFormat) {
    if (storeType & ELTextureStoreTypeGPU) {
        int format, glPixelFormat;
        switch (pixelFormat) {
            case ELPixelFormatRGBA:
                format = SOIL_LOAD_RGBA;
                glPixelFormat = GL_RGBA;
                break;
            case ELPixelFormatRGB:
                format = SOIL_LOAD_RGB;
                glPixelFormat = GL_RGB;
                break;
            case ELPixelFormatAlpha:
            case ELPixelFormatL:
            case ELPixelFormatDepth:
                format = SOIL_LOAD_L;
                glPixelFormat = GL_LUMINANCE;
                break;
            case ELPixelFormatLA:
                format = SOIL_LOAD_LA;
                glPixelFormat = GL_LUMINANCE_ALPHA;
                break;
            default:
                format = SOIL_LOAD_AUTO;
        }
        self->imageData = SOIL_load_image(imagePath.c_str(), &width, &height, &numberOfChannel, format);
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, glPixelFormat, (GLsizei) width, (GLsizei) height, 0, glPixelFormat,
                     GL_UNSIGNED_BYTE, self->imageData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);

        glValSet(this, texture);
        self->channelFormat = ELTextureChannelFormatUC;
        self->pixelFormat = pixelFormat;
    }

//    if (!(storeType & ELTextureStoreTypeCPU)) {
//        delete(self->imageData);
//        self->imageData = NULL;
//    }
    return self;
}

ELTexturePtr ELTexture::init(ELPixelFormat pixelFormat, unsigned char *imageData, ELInt width, ELInt height, ELTextureStoreType storeType) {
    if (storeType & ELTextureStoreTypeGPU) {
        int channel, format, glPixelFormat;
        switch(pixelFormat) {
            case ELPixelFormatRGBA:
                glPixelFormat = GL_RGBA;
                break;
            case ELPixelFormatRGB:
                glPixelFormat = GL_RGB;
                break;
            case ELPixelFormatAlpha:
            case ELPixelFormatL:
            case ELPixelFormatDepth:
                glPixelFormat = GL_LUMINANCE;
                break;
            case ELPixelFormatLA:
                glPixelFormat = GL_LUMINANCE_ALPHA;
                break;
            default:
                glPixelFormat = GL_RGBA;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, glPixelFormat, (GLsizei)width, (GLsizei)height, 0, glPixelFormat, GL_UNSIGNED_BYTE, imageData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);

        glValSet(this, texture);
        self->channelFormat = ELTextureChannelFormatUC;
        self->pixelFormat = pixelFormat;
    }

    if (storeType & ELTextureStoreTypeCPU) {
        self->imageData = imageData;
    } else {
        self->imageData = NULL;
        delete(imageData);
    }
    return self;
}