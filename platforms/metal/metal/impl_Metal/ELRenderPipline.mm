//
// Created by wangyang on 2017/5/24.
//

#include "platform/ELRenderPipline.h"
#import "ELMetalAdapter.h"
#import "NSObjectHolder.h"

crossplatform_var_obj(piplineDescriptor)
crossplatform_var_obj(uniformBuffer)

ELRenderPiplinePtr ELRenderPipline::init(std::string vertexShader, std::string fragmentShader) {
    id <MTLDevice> device = ELMetalAdapter::defaultAdapter()->metalDevice;
    id <MTLLibrary> defaultLibrary = [device newDefaultLibrary];
    id <MTLFunction> vertexFunc = [defaultLibrary newFunctionWithName:[NSString stringWithUTF8String:vertexShader.c_str()]];
    id <MTLFunction> fragmentFunc = [defaultLibrary newFunctionWithName:[NSString stringWithUTF8String:fragmentShader.c_str()]];
    
    MTLRenderPipelineDescriptor * piplineDesc = [MTLRenderPipelineDescriptor new];
    piplineDesc.vertexFunction = vertexFunc;
    piplineDesc.fragmentFunction = fragmentFunc;
    
    piplineDescriptorSet(this, (__bridge void *)piplineDesc);
    [NSObjectHolder retain: piplineDesc];
    return selv;
}

ELRenderPipline::~ELRenderPipline() {
    id<MTLRenderPipelineState> piplineDesc = (__bridge id<MTLRenderPipelineState>)piplineDescriptorGet(this);
    ELRelease(piplineDesc);
}

ELInt ELRenderPipline::getUniformLocation(std::string uniformName) {
    for (auto iter = uniformBuffer->attributes.begin(); iter != uniformBuffer->attributes.end(); ++iter) {
        if (iter->name == uniformName) {
            return (ELInt)(iter - uniformBuffer->attributes.begin());
        }
    }
    return -1;
}

void ELRenderPipline::setUniform(ELInt val, ELInt location) {
    ELInt offset = uniformBuffer->attributes[location].offsetInBytes;
    memcpy((void *)((unsigned char *)uniformBuffer->data() + offset), (void *)&val, sizeof(ELInt));
    uniformBuffer->flushBuffer();
}

void ELRenderPipline::setUniform(ELFloat val, ELInt location) {
    ELInt offset = uniformBuffer->attributes[location].offsetInBytes;
    memcpy((void *)((unsigned char *)uniformBuffer->data() + offset), (void *)&val, sizeof(ELFloat));
    uniformBuffer->flushBuffer();
}

void ELRenderPipline::setUniform(ELVector2 val, ELInt location) {
    ELInt offset = uniformBuffer->attributes[location].offsetInBytes;
    memcpy((void *)((unsigned char *)uniformBuffer->data() + offset), (void *)&val, sizeof(ELVector2));
    uniformBuffer->flushBuffer();
}

void ELRenderPipline::setUniform(ELVector3 val, ELInt location) {
    ELInt offset = uniformBuffer->attributes[location].offsetInBytes;
    memcpy((void *)((unsigned char *)uniformBuffer->data() + offset), (void *)&val, sizeof(ELVector3));
    uniformBuffer->flushBuffer();
}

void ELRenderPipline::setUniform(ELVector4 val, ELInt location) {
    ELInt offset = uniformBuffer->attributes[location].offsetInBytes;
    memcpy((void *)((unsigned char *)uniformBuffer->data() + offset), (void *)&val, sizeof(ELVector4));
    uniformBuffer->flushBuffer();
}

void ELRenderPipline::setUniform(ELMatrix2 val, ELInt location) {
    ELInt offset = uniformBuffer->attributes[location].offsetInBytes;
    memcpy((void *)((unsigned char *)uniformBuffer->data() + offset), (void *)&val, sizeof(ELMatrix2));
    uniformBuffer->flushBuffer();
}

void ELRenderPipline::setUniform(ELMatrix3 val, ELInt location) {
    ELInt offset = uniformBuffer->attributes[location].offsetInBytes;
    memcpy((void *)((unsigned char *)uniformBuffer->data() + offset), (void *)&val, sizeof(ELMatrix3));
    uniformBuffer->flushBuffer();
}

void ELRenderPipline::setUniform(ELMatrix4 val, ELInt location) {
    ELInt offset = uniformBuffer->attributes[location].offsetInBytes;
    memcpy((void *)((unsigned char *)uniformBuffer->data() + offset), (void *)&val, sizeof(ELMatrix4));
    uniformBuffer->flushBuffer();
}

void ELRenderPipline::bindTexture(ELTexturePtr texture, ELInt uniformLocation) {
    textures.push_back(texture);
}

void ELRenderPipline::clearState() {
    textures.clear();
}
