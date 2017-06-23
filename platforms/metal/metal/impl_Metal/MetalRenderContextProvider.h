//
//  MetalRenderContext.h
//  metal
//
//  Created by wang yang on 2017/6/22.
//  Copyright © 2017年 wang yang. All rights reserved.
//

#import <Metal/Metal.h>

@protocol MetalRenderContextProvider <NSObject>

@property (nonatomic, readonly, nullable) MTLRenderPassDescriptor *currentRenderPassDescriptor;
@property (nonatomic, readonly, nullable) id<MTLDrawable> currentDrawable;

@property (nonatomic) MTLPixelFormat colorPixelFormat;
@property (nonatomic) MTLPixelFormat depthStencilPixelFormat;
@property (nonatomic) NSUInteger sampleCount;

@end
