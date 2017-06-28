//
// Created by wangyang on 2017/5/23.
//

#ifndef EZGL_ELRENDERPASS_H
#define EZGL_ELRENDERPASS_H

#include "ELCppBase.h"
#include "ELCrossPlatformObject.h"
#include "types/EZGLTypes.h"
#include "ELRenderTarget.h"

enum ELRenderPassLoadAction {
    ELRenderPassLoadActionNotCare = 0,
    ELRenderPassLoadActionLoad = 1,
    ELRenderPassLoadActionClear = 2,
};

typedef struct {
    ELVector4 clearColor;
    ELInt clearDepth;
    ELRenderPassLoadAction loadAction;
} ELRenderPassConfig;

static inline ELRenderPassConfig ELRenderPassConfigDefault() {
    ELRenderPassConfig config;
    config.clearDepth = 1.0;
    config.clearColor = ELVector4Make(0, 0, 0, 0);
    config.loadAction = ELRenderPassLoadActionClear;
    return config;
}

classDefExt(ELRenderPass, public ELCrossPlatformObject)

public:
    ELRenderPassConfig config;
    ELRenderTargetPtr renderTarget;

    ELRenderPassPtr init(ELRenderPassConfig config, ELRenderTargetPtr renderTarget);
    ~ELRenderPass();
defEnd


#endif //EZGL_ELRENDERPASS_H
