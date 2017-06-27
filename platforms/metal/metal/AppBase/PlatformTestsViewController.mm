//
//  PlatformTestsViewController.m
//  metal
//
//  Created by wang yang on 2017/6/23.
//  Copyright © 2017年 wang yang. All rights reserved.
//

#import "PlatformTestsViewController.h"
#import "ELMetalAdapter.h"
#import "platform/BasicFlowTests.h"
#import "platform/DepthTestTests.h"

typedef struct {
    ELMatrix4 transform;
} UniformMembers;

@interface PlatformTestsViewController () {
    MTKView *_view;
    id<MTLDevice> _device;
    
    NSTimeInterval lastTime;
    NSTimeInterval currentTime;
    
    std::map<std::string, TestScene *> scenes;
    std::map<std::string, ELRenderPiplinePtr > piplines;
    ELVertexBufferPtr uniformVertexBuffer;
}
@property (weak) IBOutlet NSWindow *window;

@end

@implementation PlatformTestsViewController
- (void)viewDidLoad {
    [super viewDidLoad];
    [self initMetal];
    [self initScenes];
    
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

- (void)createPiplines {
    ELRenderPiplinePtr defaultPipline = ELRenderPipline::alloc()->init("passThroughVertex", "passThroughFragment");
    piplines["default"] = defaultPipline;
    piplines["blend"] = defaultPipline;
    
    UniformMembers members;
    members.transform = ELMatrix4Identity;
    
    uniformVertexBuffer = ELVertexBuffer::alloc()->init(&members, sizeof(UniformMembers), sizeof(UniformMembers), ELVertexBufferTypeStatic);
    ELVertexAttribute transformAttr;
    transformAttr.dataType = ELVertexAttributeDataTypeFloat;
    transformAttr.sizeInBytes = sizeof(ELMatrix4);
    transformAttr.offsetInBytes = 0;
    transformAttr.name = "transform";
    uniformVertexBuffer->addAttribute(transformAttr);
    
    defaultPipline->uniformBuffer = uniformVertexBuffer;
}

- (void)initScenes {
    [self createPiplines];
    
#define Test(Name, Scene) \
scenes[Name] = new Scene(piplines);
    
    Test("基础流程测试", BasicFlowTests);
}

// Called whenever view changes orientation or layout is changed
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size {
    
}

// Called whenever the view needs to render
- (void)drawInMTKView:(nonnull MTKView *)view {
    NSTimeInterval now = [NSDate timeIntervalSinceReferenceDate];
    NSTimeInterval deltaTime = now - lastTime;
    currentTime += deltaTime;
    lastTime = now;
    
    @autoreleasepool {
        for (auto iter = scenes.begin(); iter != scenes.end(); ++iter) {
            self.window.title = [[NSString alloc] initWithUTF8String: iter->first.c_str()];
            iter->second->update(deltaTime);
        }
    }
}
@end
