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
    ELVertexBufferType bufferType;
public:
    ELVertexBufferPtr init();
    ELVertexBufferPtr init(void *data, ELInt size, ELVertexBufferType bufferType);
    void append(void *data, ELInt size);
    ELVertexBufferPtr subbuffer(ELInt from, ELInt length);
    ELInt size();
    void clear();
    void *data();
    void addAttribute(ELVertexAttribute attribute);

defEnd

#endif //EZGL_ELVERTEXBUFFER_H
