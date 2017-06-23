//
//  GameViewController.m
//  metal
//
//  Created by wang yang on 2017/6/22.
//  Copyright © 2017年 wang yang. All rights reserved.
//

#import "GameViewController.h"
#import "platform/ELPlatform.h"
#import "ELMetalAdapter.h"

typedef struct {
    ELMatrix4 projectionMatrix;
    ELMatrix4 viewMatrix;
    ELMatrix4 modelMatrix;
} UniformMembers;


@implementation GameViewController {
    MTKView *_view;
    id<MTLDevice> _device;
    ELRendererPtr renderer;
    ELRenderPiplinePtr pipline;
    ELVertexBufferPtr cubeVertexBuffer;
    ELVertexBufferPtr uniformVertexBuffer;
    
    id <MTLTexture> diffuseTexture;
    NSTimeInterval lastTime;
    NSTimeInterval currentTime;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initMetal];
    [self setupEnv];
    [self createCube];
    [self createUniformBuffer];
    
    diffuseTexture = [self createTexture];
    lastTime = [NSDate timeIntervalSinceReferenceDate];
}

- (void)initMetal {
    _device = MTLCreateSystemDefaultDevice();
    _view = (MTKView *)self.view;
    _view.delegate = self;
    _view.device = _device;
    _view.depthStencilPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    
    if(!_device) {
        NSLog(@"Metal is not supported on this device");
        self.view = [[NSView alloc] initWithFrame:self.view.frame];
    }
    
    CGFloat screenScale = [NSScreen mainScreen].backingScaleFactor;
    ELMetalAdapter::defaultAdapter()->setup(id<MetalRenderContextProvider>(_view), _device, ELVector2Make(self.view.frame.size.width * screenScale, self.view.frame.size.height * screenScale));
}

- (void)setupEnv {
    pipline = ELRenderPipline::alloc()->init("passThroughVertex", "passThroughFragment");
    ELRenderPassConfig config;
    config.clearColor = ELVector4Make(1.0, 1.0, 0.0, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    ELRenderPassPtr renderPass = ELRenderPass::alloc()->init(config, ELRenderTarget::defaultTarget());
    renderer = ELRenderer::alloc()->init(renderPass, pipline);
}

- (void)createCube {
    static ELFloat data[] = {
        // X轴0.5处的平面
        0.5, -0.5, 0.5f, 1, 0, 0, 0, 0,
        0.5, -0.5f, -0.5f, 1, 0, 0, 0, 1,
        0.5, 0.5f, -0.5f, 1, 0, 0, 1, 1,
        0.5, 0.5, -0.5f, 1, 0, 0, 1, 1,
        0.5, 0.5f, 0.5f, 1, 0, 0, 1, 0,
        0.5, -0.5f, 0.5f, 1, 0, 0, 0, 0,
        // X轴-0.5处的平面
        -0.5, -0.5, 0.5f, -1, 0, 0, 0, 0,
        -0.5, -0.5f, -0.5f, -1, 0, 0, 0, 1,
        -0.5, 0.5f, -0.5f, -1, 0, 0, 1, 1,
        -0.5, 0.5, -0.5f, -1, 0, 0, 1, 1,
        -0.5, 0.5f, 0.5f, -1, 0, 0, 1, 0,
        -0.5, -0.5f, 0.5f, -1, 0, 0, 0, 0,
        
        -0.5, 0.5, 0.5f, 0, 1, 0, 0, 0,
        -0.5f, 0.5, -0.5f, 0, 1, 0, 0, 1,
        0.5f, 0.5, -0.5f, 0, 1, 0, 1, 1,
        0.5, 0.5, -0.5f, 0, 1, 0, 1, 1,
        0.5f, 0.5, 0.5f, 0, 1, 0, 1, 0,
        -0.5f, 0.5, 0.5f, 0, 1, 0, 0, 0,
        -0.5, -0.5, 0.5f, 0, -1, 0, 0, 0,
        -0.5f, -0.5, -0.5f, 0, -1, 0, 0, 1,
        0.5f, -0.5, -0.5f, 0, -1, 0, 1, 1,
        0.5, -0.5, -0.5f, 0, -1, 0, 1, 1,
        0.5f, -0.5, 0.5f, 0, -1, 0, 1, 0,
        -0.5f, -0.5, 0.5f, 0, -1, 0, 0, 0,
        
        -0.5, 0.5f, 0.5, 0, 0, 1, 0, 0,
        -0.5f, -0.5f, 0.5, 0, 0, 1, 0, 1,
        0.5f, -0.5f, 0.5, 0, 0, 1, 1, 1,
        0.5, -0.5f, 0.5, 0, 0, 1, 1, 1,
        0.5f, 0.5f, 0.5, 0, 0, 1, 1, 0,
        -0.5f, 0.5f, 0.5, 0, 0, 1, 0, 0,
        -0.5, 0.5f, -0.5, 0, 0, -1, 0, 0,
        -0.5f, -0.5f, -0.5, 0, 0, -1, 0, 1,
        0.5f, -0.5f, -0.5, 0, 0, -1, 1, 1,
        0.5, -0.5f, -0.5, 0, 0, -1, 1, 1,
        0.5f, 0.5f, -0.5, 0, 0, -1, 1, 0,
        -0.5f, 0.5f, -0.5, 0, 0, -1, 0, 0,
    };
    
    cubeVertexBuffer = ELVertexBuffer::alloc()->init(data, sizeof(data), sizeof(ELFloat) * 8, ELVertexBufferTypeStatic);
    ELVertexAttribute positionAttr;
    positionAttr.dataType = ELVertexAttributeDataTypeFloat;
    positionAttr.sizeInBytes = sizeof(ELFloat) * 3;
    positionAttr.offsetInBytes = 0;
    positionAttr.name = "position";
    cubeVertexBuffer->addAttribute(positionAttr);
    ELVertexAttribute colorAttr;
    colorAttr.dataType = ELVertexAttributeDataTypeFloat;
    colorAttr.sizeInBytes = sizeof(ELFloat) * 3;
    colorAttr.offsetInBytes = sizeof(ELFloat) * 3;
    colorAttr.name = "color";
    cubeVertexBuffer->addAttribute(colorAttr);
    ELVertexAttribute uvAttr;
    uvAttr.dataType = ELVertexAttributeDataTypeFloat;
    uvAttr.sizeInBytes = sizeof(ELFloat) * 2;
    uvAttr.offsetInBytes = sizeof(ELFloat) * 6;
    uvAttr.name = "uv";
    cubeVertexBuffer->addAttribute(uvAttr);
}

- (void)createUniformBuffer {
    UniformMembers members;
    members.projectionMatrix = ELMatrix4MakePerspective(90.0 * M_PI / 180.0, 640 / 480.0, 0.1, 1000);
    members.viewMatrix = ELMatrix4MakeLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
    members.modelMatrix = ELMatrix4Identity;
    
    uniformVertexBuffer = ELVertexBuffer::alloc()->init(&members, sizeof(UniformMembers), sizeof(UniformMembers), ELVertexBufferTypeStatic);
    ELVertexAttribute projectionMatrixAttr;
    projectionMatrixAttr.dataType = ELVertexAttributeDataTypeFloat;
    projectionMatrixAttr.sizeInBytes = sizeof(ELMatrix4);
    projectionMatrixAttr.offsetInBytes = 0;
    projectionMatrixAttr.name = "projectionMatrix";
    uniformVertexBuffer->addAttribute(projectionMatrixAttr);
    ELVertexAttribute viewMatrixAttr;
    viewMatrixAttr.dataType = ELVertexAttributeDataTypeFloat;
    viewMatrixAttr.sizeInBytes =  sizeof(ELMatrix4);
    viewMatrixAttr.offsetInBytes =  sizeof(ELMatrix4);
    viewMatrixAttr.name = "viewMatrix";
    uniformVertexBuffer->addAttribute(viewMatrixAttr);
    ELVertexAttribute modelMatrixAttr;
    modelMatrixAttr.dataType = ELVertexAttributeDataTypeFloat;
    modelMatrixAttr.sizeInBytes = sizeof(ELMatrix4);
    modelMatrixAttr.offsetInBytes = sizeof(ELMatrix4) * 2;
    modelMatrixAttr.name = "modelMatrix";
    uniformVertexBuffer->addAttribute(modelMatrixAttr);
    
    pipline->uniformBuffer = uniformVertexBuffer;
}

// Called whenever view changes orientation or layout is changed
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size {
    
}

// Called whenever the view needs to render
- (void)drawInMTKView:(nonnull MTKView *)view {
    NSTimeInterval now = [NSDate timeIntervalSinceReferenceDate];
    currentTime += now - lastTime;
    lastTime = now;
    
    UniformMembers members;
    members.projectionMatrix = ELMatrix4MakePerspective(90.0 * M_PI / 180.0, 640 / 480.0, 0.1, 1000);
    members.viewMatrix = ELMatrix4MakeLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
    members.modelMatrix = ELMatrix4MakeRotation(currentTime, 1, 1, 1);
    
    uniformVertexBuffer->clear();
    uniformVertexBuffer->append(&members, sizeof(UniformMembers));
    uniformVertexBuffer->flushBuffer();
    
    MTLDepthStencilDescriptor *depthStencilDescriptor = [MTLDepthStencilDescriptor new];
    depthStencilDescriptor.depthCompareFunction = MTLCompareFunctionLessEqual;
    depthStencilDescriptor.depthWriteEnabled = YES;
    
    id <MTLDepthStencilState> depthState = [_device newDepthStencilStateWithDescriptor:depthStencilDescriptor];
    
    @autoreleasepool {
        renderer->prepare();
        id <MTLRenderCommandEncoder> encoder = (__bridge id <MTLRenderCommandEncoder> )renderer->__crossplatformFetchObject("currentCommandEncoder");
        [encoder setFragmentTexture:diffuseTexture atIndex:0];
        [encoder setDepthStencilState:depthState];
        renderer->drawPrimitives(ELPrimitivesTypeTriangle, cubeVertexBuffer);
        renderer->endRender();
    }
}

- (id<MTLTexture>)createTexture {
    NSImage *image = [NSImage imageNamed: @"texture.jpg"];
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
    
    
    // Create a suitable bitmap context for extracting the bits of the image
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
    
    id<MTLTexture> texture = [_device newTextureWithDescriptor:textureDescriptor];
    MTLRegion region = MTLRegionMake2D(0, 0, width, height);
    [texture replaceRegion:region mipmapLevel:0 withBytes:rawData bytesPerRow:bytesPerRow];
    return texture;
}
@end

