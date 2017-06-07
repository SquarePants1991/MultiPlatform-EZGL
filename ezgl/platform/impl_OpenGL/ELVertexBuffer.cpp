//
// Created by wangyang on 2017/5/23.
//

#include "../ELVertexBuffer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

crossplatform_var_int(vbo)

static void genVBO(ELVertexBufferPtr buffer) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GLenum glBufferType = buffer->bufferType == ELVertexBufferTypeDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
    glBufferData(GL_ARRAY_BUFFER, buffer->size(), buffer->data(), glBufferType);
    buffer->__crossplatformAttach("vbo", (ELInt)vbo);
}

static void updateVBO(ELVertexBufferPtr buffer) {
    GLuint vbo = (GLuint)(buffer->__crossplatformFetchInt("vbo"));
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GLenum glBufferType = buffer->bufferType == ELVertexBufferTypeDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
    glBufferData(GL_ARRAY_BUFFER, buffer->size(), buffer->data(), glBufferType);
}

ELVertexBufferPtr ELVertexBuffer::init() {
    genVBO(self);
    return self;
}

ELVertexBufferPtr ELVertexBuffer::init(void *data, ELInt sizeInBytes, ELInt vertexSizeInBytes, ELVertexBufferType bufferType) {
    for (int i = 0; i < sizeInBytes; ++i) {
        buffer.push_back(*((unsigned char *)data + i));
    }
    self->useIndex = false;
    self->bufferType = bufferType;
    self->vertexSizeInBytes = vertexSizeInBytes;
    genVBO(self);
    return self;
}

void ELVertexBuffer::append(void *data, ELInt size) {
    for (int i = 0; i < size; ++i) {
        buffer.push_back(*((unsigned char *)data + i));
    }
    updateVBO(self);
}

ELInt ELVertexBuffer::size() {
    return buffer.size();
}

ELInt ELVertexBuffer::vertexCount() {
    if (useIndex) {
        //TODO: 为支持索引留下缺口
        return 0;
    }
    return buffer.size() / vertexSizeInBytes;
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
    ELVertexBufferPtr subBuffer = ELVertexBuffer::alloc()->init(bufferStart, length, self->vertexSizeInBytes, bufferType);
    return subBuffer;
}