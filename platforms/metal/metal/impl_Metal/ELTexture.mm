//
// Created by wangyang on 2017/5/24.
//

#include "platform/ELTexture.h"
#import "ELMetalAdapter.h"
#import <Cocoa/Cocoa.h>

crossplatform_var_obj(mtlTexture)

ELTexturePtr ELTexture::init(ELPixelFormat pixelFormat, unsigned char *imageData, ELInt width, ELInt height, ELTextureStoreType storeType) {
//    id <MTLDevice> device = ELMetalAdapter::defaultAdapter()->metalDevice;
//    MTLTextureDescriptor textureDescriptor = [MTLTextureDescriptor alloc];
//    textureDescriptor.width
//    [device newTextureWithDescriptor:<#(nonnull MTLTextureDescriptor *)#>]
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
    
    NSUInteger width = CGImageGetWidth(imageRef);
    NSUInteger height = CGImageGetHeight(imageRef);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    uint8_t *rawData = (uint8_t *)calloc(height * width * 4, sizeof(uint8_t));
    NSUInteger bytesPerPixel = 4;
    NSUInteger bytesPerRow = bytesPerPixel * width;
    NSUInteger bitsPerComponent = 8;
    CGContextRef context = CGBitmapContextCreate(rawData, width, height,
                                                 bitsPerComponent, bytesPerRow, colorSpace,
                                                 kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpace);
    
    // Flip the context so the positive Y axis points down
    CGContextTranslateCTM(context, 0, height);
    CGContextScaleCTM(context, 1, -1);
    
    CGContextDrawImage(context, CGRectMake(0, 0, width, height), imageRef);
    CGContextRelease(context);
    
    MTLTextureDescriptor *textureDescriptor = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm
                                                                                                 width:width
                                                                                                height:height
                                                                                             mipmapped:YES];
    
    id<MTLTexture> texture = [device newTextureWithDescriptor:textureDescriptor];
    MTLRegion region = MTLRegionMake2D(0, 0, width, height);
    [texture replaceRegion:region mipmapLevel:0 withBytes:rawData bytesPerRow:bytesPerRow];
    
    return selv;
}

ELTexture::~ELTexture() {
    
}
