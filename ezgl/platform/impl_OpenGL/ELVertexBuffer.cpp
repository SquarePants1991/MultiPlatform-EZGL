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

static void genIBO(ELVertexBufferPtr buffer) {
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    GLenum glBufferType = buffer->bufferType == ELVertexBufferTypeDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer->indexBufferSize(), buffer->indexData(), glBufferType);
    buffer->__crossplatformAttach("ibo", (ELInt)ibo);
}

static void updateIBO(ELVertexBufferPtr buffer) {
    GLuint ibo = (GLuint)(buffer->__crossplatformFetchInt("ibo"));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    GLenum glBufferType = buffer->bufferType == ELVertexBufferTypeDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer->indexBufferSize(), buffer->indexData(), glBufferType);
}

ELVertexBufferPtr ELVertexBuffer::init(ELInt vertexSizeInBytes, ELVertexBufferType bufferType) {
    selv->useIndex = false;
    selv->bufferType = bufferType;
    selv->vertexSizeInBytes = vertexSizeInBytes;
    genVBO(selv);
    return selv;
}

ELVertexBufferPtr ELVertexBuffer::init(void *data, ELInt sizeInBytes, ELInt vertexSizeInBytes, ELVertexBufferType bufferType) {
    for (int i = 0; i < sizeInBytes; ++i) {
        buffer.push_back(*((unsigned char *)data + i));
    }
    selv->useIndex = false;
    selv->bufferType = bufferType;
    selv->vertexSizeInBytes = vertexSizeInBytes;
    genVBO(selv);
    return selv;
}

void ELVertexBuffer::append(void *data, ELInt size) {
    for (int i = 0; i < size; ++i) {
        buffer.push_back(*((unsigned char *) data + i));
    }
}

void ELVertexBuffer::flushBuffer() {
    updateVBO(selv);
}

ELInt ELVertexBuffer::size() {
    return buffer.size();
}

ELInt ELVertexBuffer::vertexCount() {
    if (useIndex) {
        return indexBuffer.size();
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
    ELVertexBufferPtr subBuffer = ELVertexBuffer::alloc()->init(bufferStart, length, selv->vertexSizeInBytes, bufferType);
    return subBuffer;
}

void ELVertexBuffer::enableIndex() {
    if (selv->useIndex) {
        return;
    }
    selv->useIndex = true;
    genIBO(selv);
}

void ELVertexBuffer::appendIndex(void *data, ELInt size) {
    if (selv->useIndex) {
        for (int i = 0; i < size; ++i) {
            indexBuffer.push_back(*((ELInt *)data + i));
        }
    }
}

void ELVertexBuffer::appendIndex(ELInt index) {
    if (selv->useIndex) {
        indexBuffer.push_back(index);
    }
}

void ELVertexBuffer::clearIndex() {
    if (selv->useIndex) {
        indexBuffer.clear();
    }
}

ELInt *ELVertexBuffer::indexData() {
    return (ELInt *)indexBuffer.data();
}

ELInt ELVertexBuffer::indexBufferSize() {
    return indexBuffer.size() * sizeof(ELInt);
}

void ELVertexBuffer::flushIndexBuffer() {
    updateIBO(selv);
}