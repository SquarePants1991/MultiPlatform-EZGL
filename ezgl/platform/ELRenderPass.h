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
    ELRenderPassLoadActionClear,
    ELRenderPassLoadActionLoad
};

typedef struct {
    ELVector4 clearColor;
    ELRenderPassLoadAction loadAction;
} ELRenderPassConfig;

classDefExt(ELRenderPass, ELCrossPlatformObject)

public:
    ELRenderPassConfig config;
    ELRenderTargetPtr renderTarget;

    ELRenderPassPtr init(ELRenderPassConfig config, ELRenderTargetPtr renderTarget);

defEnd


#endif //EZGL_ELRENDERPASS_H
