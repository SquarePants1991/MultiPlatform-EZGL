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
#import "platform/BlendModeTests.h"
#import "platform/IndexBufferTests.h"
#import "platform/StencilTestTests.h"
#import "platform/AlphaTestTests.h"

typedef struct {
    ELMatrix4 transform;
    ELVector4 color;
} UniformMembers;

@interface PlatformTestsViewController () {
    MTKView *_view;
    id<MTLDevice> _device;
    
    NSTimeInterval lastTime;
    NSTimeInterval currentTime;
    
    std::string currentSceneName;
    std::map<std::string, TestScene *> scenes;
    std::map<std::string, ELRenderPiplinePtr > piplines;
}
@property (weak) IBOutlet NSWindow *window;

@end

@implementation PlatformTestsViewController
- (void)viewDidLoad {
    [super viewDidLoad];
    [self initMetal];
    [self initScenes];
    
    lastTime = [NSDate timeIntervalSinceReferenceDate];
    
    [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskKeyDown handler:^NSEvent * _Nullable(NSEvent * _Nonnull event) {
        [self keyDown:event];
        return event;
    }];
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
    ELRenderPiplinePtr piplineBlend = ELRenderPipline::alloc()->init("passThroughVertex", "passThroughFragmentBlend");
    piplines["blend"] = piplineBlend;
    
    UniformMembers members;
    members.transform = ELMatrix4Identity;
    
    ELVertexBufferPtr uniformVertexBuffer = ELVertexBuffer::alloc()->init(&members, sizeof(UniformMembers), sizeof(UniformMembers), ELVertexBufferTypeStatic);
    ELVertexAttribute transformAttr;
    transformAttr.dataType = ELVertexAttributeDataTypeFloat;
    transformAttr.sizeInBytes = sizeof(ELMatrix4);
    transformAttr.offsetInBytes = 0;
    transformAttr.name = "transform";
    uniformVertexBuffer->addAttribute(transformAttr);
    
    ELVertexAttribute colorAttr;
    colorAttr.dataType = ELVertexAttributeDataTypeFloat;
    colorAttr.sizeInBytes = sizeof(ELVector4);
    colorAttr.offsetInBytes = sizeof(ELMatrix4);
    colorAttr.name = "color";
    uniformVertexBuffer->addAttribute(colorAttr);
    
    defaultPipline->uniformBuffer = uniformVertexBuffer;
    
    uniformVertexBuffer = ELVertexBuffer::alloc()->init(&members, sizeof(UniformMembers), sizeof(UniformMembers), ELVertexBufferTypeStatic);
    uniformVertexBuffer->addAttribute(transformAttr);
    uniformVertexBuffer->addAttribute(colorAttr);
    piplineBlend->uniformBuffer = uniformVertexBuffer;
}

- (void)initScenes {
    ELAssets::shared()->addSearchPath([[NSBundle mainBundle].resourcePath UTF8String]);
    [self createPiplines];
    
#define Test(Name, Scene) \
scenes[Name] = new Scene(piplines);
    
    Test("基础流程测试", BasicFlowTests);
    Test("深度测试", DepthTestTests);
    Test("Blend模式测试", BlendModeTests);
    Test("顶点索引测试", IndexBufferTests);
    Test("StencilTest测试", StencilTestTests);
    Test("AlphaTest测试", AlphaTestTests);
    
    currentSceneName = scenes.begin()->first;
    self.window.title = [[NSString alloc] initWithUTF8String: currentSceneName.c_str()];
}

- (void)prevScene {
    auto iter = scenes.find(currentSceneName);
    if (iter == scenes.begin()) {
        currentSceneName = scenes.rbegin()->first;
    } else {
        iter--;
        currentSceneName = iter->first;
    }
    self.window.title = [[NSString alloc] initWithUTF8String: currentSceneName.c_str()];
}

- (void)nextScene {
    auto iter = scenes.find(currentSceneName);
    iter++;
    if (iter == scenes.end()) {
        iter = scenes.begin();
    }
    currentSceneName = iter->first;
    self.window.title = [[NSString alloc] initWithUTF8String: currentSceneName.c_str()];
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
        TestScene *scene = scenes.at(currentSceneName);
        if (scene) {
            scene->update(deltaTime);
        }
    }
}

- (void)keyDown:(NSEvent *)event {
    switch(event.keyCode) {
        case 123: // 左箭头
        [self prevScene];
        break;
        case 124: // 右箭头
        [self nextScene];
        break;
        default:
        break;
    }
}
@end
