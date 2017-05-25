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

//static void genVAO(ELVertexBufferPtr buffer) {
//    GLuint vao;
//    GLuint vbo = (GLuint)(buffer->__crossplatformFetchInt("vbo"));
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//
//    for (int i = 0; i < buffer->attributes.size(); ++i) {
//        ELVertexAttribute attr = buffer->attributes.at(i);
//        glGetAttribLocation();
//    }
//
//    glBindVertexArray(0);
//}

ELVertexBufferPtr ELVertexBuffer::init() {
    genVBO(self);
    return self;
}

ELVertexBufferPtr ELVertexBuffer::init(void *data, ELInt size, ELVertexBufferType bufferType) {
    for (int i = 0; i < size; ++i) {
        buffer.push_back(*((unsigned char *)data + i));
    }
    self->bufferType = bufferType;
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
    ELVertexBufferPtr subBuffer = ELVertexBuffer::alloc()->init(bufferStart, length, bufferType);
    return subBuffer;
}