//
// Created by wangyang on 2017/5/24.
//

#include "platform/ELTexture.h"
#import "ELMetalAdapter.h"
#import "NSObjectHolder.h"

crossplatform_var_obj(mtlTexture)

static MTLPixelFormat PixelFormatMap[] = {
    MTLPixelFormatRGBA8Unorm,
    MTLPixelFormatBGRA8Unorm,
    MTLPixelFormatR16Float,
    MTLPixelFormatDepth32Float_Stencil8,
    MTLPixelFormatRG8Uint,
    MTLPixelFormatR8Uint
};

ELTexturePtr ELTexture::init(ELPixelFormat pixelFormat, unsigned char *imageData, ELInt width, ELInt height, ELTextureStoreType storeType) {
    selv->pixelFormat = pixelFormat;
    selv->width = width;
    selv->height = height;
    
    int bytesPerRow = 0;
    switch (pixelFormat) {
        case ELPixelFormatRGB:
            bytesPerRow = width * 4 * 8;
            selv->numberOfChannel = 4;
            selv->channelFormat = ELTextureChannelFormatUC;
            break;
        case ELPixelFormatRGBA:
            bytesPerRow = width * 4 * 8;
            selv->numberOfChannel = 4;
            selv->channelFormat = ELTextureChannelFormatUC;
            break;
        case ELPixelFormatAlpha:
            bytesPerRow = width * 8;
            selv->numberOfChannel = 1;
            selv->channelFormat = ELTextureChannelFormatUC;
            break;
        case ELPixelFormatDepth:
            bytesPerRow = width * 32;
            break;
        case ELPixelFormatLA:
            bytesPerRow = width * 2 * 8;
            break;
        case ELPixelFormatL:
            bytesPerRow = width * 8;
            break;
        default:
            break;
    }
    
    id <MTLDevice> device = ELMetalAdapter::defaultAdapter()->metalDevice;
    MTLTextureDescriptor *textureDescriptor = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:PixelFormatMap[pixelFormat] width:width height:height mipmapped:YES];
    // 保持Metal下纹理的默认设置
    textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead | MTLTextureUsageShaderWrite;
    textureDescriptor.storageMode = MTLStorageModePrivate;
    id<MTLTexture> texture = [device newTextureWithDescriptor:textureDescriptor];
    MTLRegion region = MTLRegionMake2D(0, 0, width, height);
    if (imageData) {
        [texture replaceRegion:region mipmapLevel:0 withBytes:imageData bytesPerRow:bytesPerRow];
    }
    mtlTextureSet(this, (__bridge void *)texture);
    ELRetain(texture);
    return selv;
}

ELTexturePtr ELTexture::init(std::string imagePath, ELTextureStoreType storeType, ELPixelFormat pixelFormat) {
    id <MTLDevice> device = ELMetalAdapter::defaultAdapter()->metalDevice;
    
    // for OSX
    NSString *path = [NSString stringWithCString:imagePath.c_str() encoding:NSUTF8StringEncoding];
    NSImage *image = [[NSImage alloc] initWithContentsOfFile: path];
    NSData * imageData = [image TIFFRepresentation];
    CGImageRef imageRef;
    if (imageData)
    {
        CGImageSourceRef imageSource =
        CGImageSourceCreateWithData(
                                    (CFDataRef)imageData,  NULL);
        
        imageRef = CGImageSourceCreateImageAtIndex(
                                                   imageSource, 0, NULL);
    } else {
        return nil;
    }
    
    width = (ELInt)CGImageGetWidth(imageRef);
    height = (ELInt)CGImageGetHeight(imageRef);
    selv->pixelFormat = ELPixelFormatRGBA;
    selv->numberOfChannel = 4;
    selv->channelFormat = ELTextureChannelFormatUC;
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    uint8_t *rawData = (uint8_t *)calloc(height * width * 4, sizeof(uint8_t));
    NSUInteger bytesPerPixel = 4;
    NSUInteger bytesPerRow = bytesPerPixel * width;
    NSUInteger bitsPerComponent = 8;
    CGContextRef context = CGBitmapContextCreate(rawData, width, height,
                                                 bitsPerComponent, bytesPerRow, colorSpace,
                                                 kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpace);
    
    CGContextDrawImage(context, CGRectMake(0, 0, width, height), imageRef);
    CGContextRelease(context);
    
    MTLTextureDescriptor *textureDescriptor = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm
                                                                                                 width:width
                                                                                                height:height
                                                                                             mipmapped:YES];
    
    id<MTLTexture> texture = [device newTextureWithDescriptor:textureDescriptor];
    MTLRegion region = MTLRegionMake2D(0, 0, width, height);
    [texture replaceRegion:region mipmapLevel:0 withBytes:rawData bytesPerRow:bytesPerRow];
    
    mtlTextureSet(this, (__bridge void *)texture);
    [NSObjectHolder retain: texture];
    return selv;
}

ELTexture::~ELTexture() {
    id<MTLTexture> texture = (__bridge id<MTLTexture> )mtlTextureGet(this);
    if (texture) {
        ELRelease(texture);
    }
}
