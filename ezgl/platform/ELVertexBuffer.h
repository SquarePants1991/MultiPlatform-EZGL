//
// Created by wangyang on 2017/5/23.
//

#ifndef EZGL_ELVERTEXBUFFER_H
#define EZGL_ELVERTEXBUFFER_H

#include "ELCppBase.h"
#include "ELCrossPlatformObject.h"
#include <vector>

typedef struct {
    std::string name;
    ELInt offsetInBytes;
    ELInt sizeInBytes;
} ELVertexAttribute;

classDefExt(ELVertexBuffer, ELCrossPlatformObject)

public:
    std::vector<ELVertexAttribute> attributes;
    std::vector<unsigned char> buffer;
public:
    ELVertexBufferPtr init(void *data, ELInt size);
    void append(void *data, ELInt size);
    ELVertexBufferPtr subbuffer(ELInt from, ELInt length);
    void clear();
    void *data();
    void addAttribute(ELVertexAttribute attribute);

defEnd

#endif //EZGL_ELVERTEXBUFFER_H
