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

@implementation GameViewController {
    MTKView *_view;
    id<MTLDevice> _device;
    ELRendererPtr renderer;
    ELRenderPiplinePtr pipline;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initMetal];
    [self initPipline];
}

- (void)initMetal {
    _device = MTLCreateSystemDefaultDevice();
    _view = (MTKView *)self.view;
    _view.delegate = self;
    _view.device = _device;
    
    if(!_device) {
        NSLog(@"Metal is not supported on this device");
        self.view = [[NSView alloc] initWithFrame:self.view.frame];
    }
    
    CGFloat screenScale = [NSScreen mainScreen].backingScaleFactor;
    ELMetalAdapter::defaultAdapter()->setup(id<MetalRenderContextProvider>(_view), _device, ELVector2Make(self.view.frame.size.width * screenScale, self.view.frame.size.height * screenScale));
}

- (void)initPipline {
    pipline = ELRenderPipline::alloc()->init("passThroughVertex", "passThroughFragment");
    ELRenderPassConfig config;
    config.clearColor = ELVector4Make(0, 1.0, 0.0, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    ELRenderPassPtr renderPass = ELRenderPass::alloc()->init(config, ELRenderTarget::defaultTarget());
    renderer = ELRenderer::alloc()->init(renderPass, pipline);
}

// Called whenever view changes orientation or layout is changed
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size {
    
}

// Called whenever the view needs to render
- (void)drawInMTKView:(nonnull MTKView *)view {
    @autoreleasepool {
        renderer->prepare();
        
        renderer->endRender();
    }
}
@end

