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
    ~ELVertexBuffer();
    void flushBuffer();

    void append(void *data, ELInt size) {
        for (int i = 0; i < size; ++i) {
            buffer.push_back(*((unsigned char *) data + i));
        }
    }

    ELVertexBufferPtr subbuffer(ELInt from, ELInt length) {
        void *bufferData = data();
        void *bufferStart = (void *)((unsigned char *)bufferData + from);
        ELVertexBufferPtr subBuffer = ELVertexBuffer::alloc()->init(bufferStart, length, selv->vertexSizeInBytes, bufferType);
        return subBuffer;
    }

    ELInt size() {
        return buffer.size();
    }

    ELInt vertexCount() {
        if (useIndex) {
            return indexBuffer.size();
        }
        return buffer.size() / vertexSizeInBytes;
    }

    void clear() {
        buffer.clear();
    }
    void * data() {
        return (void *)buffer.data();
    }

    void addAttribute(ELVertexAttribute attribute) {
        attributes.push_back(attribute);
    }

    // 索引操作
    void enableIndex();
    void flushIndexBuffer();

    void appendIndex(void *data, ELInt size) {
        if (selv->useIndex) {
            for (int i = 0; i < size; ++i) {
                indexBuffer.push_back(*((ELInt *)data + i));
            }
        }
    }

    void appendIndex(ELInt index) {
        if (selv->useIndex) {
            indexBuffer.push_back(index);
        }
    }

    void clearIndex() {
        if (selv->useIndex) {
            indexBuffer.clear();
        }
    }

    ELInt *indexData() {
        return (ELInt *)indexBuffer.data();
    }

    ELInt indexBufferSize() {
        return indexBuffer.size() * sizeof(ELInt);
    }


defEnd

#endif //EZGL_ELVERTEXBUFFER_H
