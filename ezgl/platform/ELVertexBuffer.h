//
// Created by wangyang on 2017/5/23.
//

#ifndef EZGL_ELVERTEXBUFFER_H
#define EZGL_ELVERTEXBUFFER_H

#include "ELCppBase.h"
#include "ELCrossPlatformObject.h"
#include <vector>

enum ELVertexAttributeDataType {
    ELVertexAttributeDataTypeFloat,
    ELVertexAttributeDataTypeInt,
};

typedef struct {
    std::string name;
    ELInt offsetInBytes;
    ELInt sizeInBytes;
    ELVertexAttributeDataType dataType;
} ELVertexAttribute;

enum ELVertexBufferType {
    ELVertexBufferTypeStatic,
    ELVertexBufferTypeDynamic
};

classDefExt(ELVertexBuffer, public ELCrossPlatformObject)

public:
    std::vector<ELVertexAttribute> attributes;
    std::vector<unsigned char> buffer;
    std::vector<ELInt> indexBuffer;
    ELVertexBufferType bufferType;
    ELInt vertexSizeInBytes;
    bool useIndex; // 是否使用索引
public:
    ELVertexBufferPtr init(ELInt vertexSizeInBytes, ELVertexBufferType bufferType);
    ELVertexBufferPtr init(void *data, ELInt sizeInBytes, ELInt vertexSizeInBytes,ELVertexBufferType bufferType);
    void append(void *data, ELInt size);
    void flushBuffer();
    ELVertexBufferPtr subbuffer(ELInt from, ELInt length);
    ELInt size();
    ELInt vertexCount();
    void clear();
    void *data();
    void addAttribute(ELVertexAttribute attribute);

    // 索引操作
    void enableIndex();
    void appendIndex(void *data, ELInt size);
    void appendIndex(ELInt index);
    void clearIndex();
    ELInt *indexData();
    ELInt indexBufferSize();
    void flushIndexBuffer();
defEnd

#endif //EZGL_ELVERTEXBUFFER_H
