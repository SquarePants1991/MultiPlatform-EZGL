//
//  PlatformTestsViewController.m
//  metal
//
//  Created by wang yang on 2017/6/23.
//  Copyright © 2017年 wang yang. All rights reserved.
//

#import "PlatformTestsViewController.h"
#import "ELMetalAdapter.h"
#import "BasicFlowTests.h"

#define Test(Name, Scene) \
scenes[Name] = new Scene();

typedef struct {
    ELMatrix4 projectionMatrix;
    ELMatrix4 viewMatrix;
    ELMatrix4 modelMatrix;
} UniformMembers;

@interface PlatformTestsViewController () {
    MTKView *_view;
    id<MTLDevice> _device;
    
    NSTimeInterval lastTime;
    NSTimeInterval currentTime;
    
    std::map<std::string, TestScene *> scenes;
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

- (void)initScenes {
    Test("基本流程测试", BasicFlowTests);
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
