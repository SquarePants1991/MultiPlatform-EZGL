//
// Created by wangyang on 2017/5/23.
//

#include "../ELVertexBuffer.h"

crossplatform_var(ELInt, vbo)
crossplatform_var(ELInt, vao)

ELVertexBufferPtr ELVertexBuffer::init(void *data, ELInt size) {
    for (int i = 0; i < size; ++i) {
        buffer.push_back(*((unsigned char *)data + i));
    }
}

void ELVertexBuffer::append(void *data, ELInt size) {
    for (int i = 0; i < size; ++i) {
        buffer.push_back(*((unsigned char *)data + i));
    }
}

void ELVertexBuffer::clear() {
    buffer.clear();
}

void * ELVertexBuffer::data() {
    return (void *)buffer.data();
}

void ELVertexBuffer::addAttribute(ELVertexAttribute attribute) {
    attributes.push_back(attribute);
}

ELVertexBufferPtr ELVertexBuffer::subbuffer(ELInt from, ELInt length) {
    void *bufferData = data();
    void *bufferStart = (void *)((unsigned char *)bufferData + from);
    ELVertexBufferPtr subBuffer = ELVertexBuffer::alloc()->init(bufferStart, length);
    return subBuffer;
}