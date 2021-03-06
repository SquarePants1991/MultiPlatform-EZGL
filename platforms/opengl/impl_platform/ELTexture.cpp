//
// Created by wangyang on 2017/5/24.
//

#include "platform/ELTexture.h"
#include "soil/SOIL.h"
#include <GL/glew.h>

crossplatform_var_int(glVal)

ELTexturePtr ELTexture::init(std::string imagePath, ELTextureStoreType storeType, ELPixelFormat pixelFormat) {
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
    selv->imageData = SOIL_load_image(imagePath.c_str(), &width, &height, &numberOfChannel, format);
    if (storeType & ELTextureStoreTypeGPU) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, glPixelFormat, (GLsizei) width, (GLsizei) height, 0, glPixelFormat,
                     GL_UNSIGNED_BYTE, selv->imageData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glBindTexture(GL_TEXTURE_2D, 0);

        glValSet(this, texture);
        selv->channelFormat = ELTextureChannelFormatUC;
        selv->pixelFormat = pixelFormat;
    }

    if (!(storeType & ELTextureStoreTypeCPU)) {
        delete(selv->imageData);
        selv->imageData = NULL;
    }
    selv->textureType = ELTextureType2D;
    return selv;
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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glBindTexture(GL_TEXTURE_2D, 0);

        glValSet(this, texture);
        selv->channelFormat = ELTextureChannelFormatUC;
        selv->pixelFormat = pixelFormat;
    }

    if (storeType & ELTextureStoreTypeCPU) {
        selv->imageData = imageData;
    } else {
        selv->imageData = NULL;
        delete(imageData);
    }
    selv->textureType = ELTextureType2D;
    return selv;
}

// Right, Left, Top, Bottom, Back, Front
ELTexturePtr ELTexture::init(std::vector<std::string> imagePaths, ELTextureStoreType storeType, ELPixelFormat pixelFormat) {
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

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        ELInt faceIndex = 0;
        for (auto iter = imagePaths.begin(); iter != imagePaths.end(); ++iter) {
            ELInt width, height, numberOfChannel;
            unsigned char *imageData = SOIL_load_image(iter->c_str(), &width, &height, &numberOfChannel, format);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + faceIndex, 0, glPixelFormat, (GLsizei)width, (GLsizei)height, 0, glPixelFormat, GL_UNSIGNED_BYTE, imageData);
            delete(imageData);
            faceIndex++;
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameterf( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexParameterf( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
        glBindTexture(GL_TEXTURE_2D, 0);

        glValSet(this, texture);
        selv->channelFormat = ELTextureChannelFormatUC;
        selv->pixelFormat = pixelFormat;
    }

    selv->textureType = ELTextureTypeCube;
    return selv;

}

ELTexture::~ELTexture() {

}