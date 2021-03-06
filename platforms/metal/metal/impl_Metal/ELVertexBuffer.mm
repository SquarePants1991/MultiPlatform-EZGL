//
// Created by wangyang on 2017/5/23.
//

#include "platform/ELVertexBuffer.h"
#import "ELMetalAdapter.h"
#import "NSObjectHolder.h"

crossplatform_var_obj(vertexBuffer)
crossplatform_var_obj(indexBuffer)

ELVertexBufferPtr ELVertexBuffer::init(ELInt vertexSizeInBytes, ELVertexBufferType bufferType) {
    selv->useIndex = false;
    selv->bufferType = bufferType;
    selv->vertexSizeInBytes = vertexSizeInBytes;
    return selv;
}

ELVertexBufferPtr ELVertexBuffer::init(void *data, ELInt sizeInBytes, ELInt vertexSizeInBytes, ELVertexBufferType bufferType) {
    for (int i = 0; i < sizeInBytes; ++i) {
        buffer.push_back(*((unsigned char *)data + i));
    }
    selv->useIndex = false;
    selv->bufferType = bufferType;
    selv->vertexSizeInBytes = vertexSizeInBytes;
    
    id <MTLBuffer> vertexBuffer = [ELMetalAdapter::defaultAdapter()->metalDevice newBufferWithBytes:buffer.data() length:buffer.size() options:MTLResourceCPUCacheModeDefaultCache];
    vertexBufferSet(this, (__bridge void *)vertexBuffer);
    ELRetain(vertexBuffer);
    return selv;
}

ELVertexBuffer::~ELVertexBuffer() {
    id <MTLBuffer> vertexBuffer = (__bridge id <MTLBuffer>)vertexBufferGet(this);
    if (vertexBuffer) {
        ELRelease(vertexBuffer);
    }
}

void ELVertexBuffer::flushBuffer() {
    id <MTLBuffer> vertexBuffer = (__bridge id <MTLBuffer>)vertexBufferGet(this);
    if (vertexBuffer) {
         ELRelease(vertexBuffer);
    }
    
    vertexBuffer = (__bridge id <MTLBuffer>)vertexBufferGet(this);
    vertexBuffer = [ELMetalAdapter::defaultAdapter()->metalDevice newBufferWithBytes:buffer.data() length:buffer.size() options:MTLResourceCPUCacheModeDefaultCache];
    vertexBufferSet(this, (__bridge void *)vertexBuffer);
    ELRetain(vertexBuffer);
}

void ELVertexBuffer::enableIndex() {
    if (selv->useIndex) {
        return;
    }
    selv->useIndex = true;
}

void ELVertexBuffer::flushIndexBuffer() {
    id <MTLBuffer> mtlIndexBuffer = (__bridge id <MTLBuffer>)indexBufferGet(this);
    if (mtlIndexBuffer) {
        ELRelease(mtlIndexBuffer);
    }
    
    mtlIndexBuffer = [ELMetalAdapter::defaultAdapter()->metalDevice newBufferWithBytes:indexBuffer.data() length:indexBuffer.size() * sizeof(ELInt) options:MTLResourceCPUCacheModeDefaultCache];
    indexBufferSet(this, (__bridge void *)mtlIndexBuffer);
    ELRetain(mtlIndexBuffer);
}
