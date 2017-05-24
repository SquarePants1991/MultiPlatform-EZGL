//
// Created by wangyang on 2017/5/24.
//

#include "../ELRenderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../types/EZGLTypes.h"
#include "../ELPlatform.h"

ELRendererPtr ELRenderer::init(ELRenderPassPtr renderPass, ELRenderPiplinePtr pipline) {
    self->renderPass = renderPass;
    self->pipline = pipline;
    std::string s = stringify(rrrr);
    return self;
}

void ELRenderer::prepare() {
    if (renderPass->config.loadAction == ELRenderPassLoadActionClear) {
        ELVector4 clearColor = renderPass->config.clearColor;
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        GLbitfield clearMask = renderPass->renderTarget->colorBufferEnabled ? GL_COLOR_BUFFER_BIT : 0;
        clearMask |= renderPass->renderTarget->depthBufferEnabled ? GL_DEPTH_BUFFER_BIT : 0;
        clearMask |= renderPass->renderTarget->stencilBufferEnabled ? GL_STENCIL_BUFFER_BIT : 0;
        glClear(clearMask);
    }
    GLuint program = this->pipline->__crossplatformFetchInt("program");
    glUseProgram(program);
}

void ELRenderer::endRender() {

}

void ELRenderer::drawPrimitives(ELPrimitivesType type, ELVertexBufferPtr vertexBuffer) {
    if (vertexBuffer->attributes.size() == 0) {
        return;
    }
    GLuint vbo = vertexBuffer->__crossplatformFetchInt("vbo");
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GLuint program = this->pipline->__crossplatformFetchInt("program");
    ELInt  vertexSize = 0;
    for (int i = 0; i < vertexBuffer->attributes.size(); ++i) {
        ELVertexAttribute attr = vertexBuffer->attributes.at(i);
        GLuint loc = glGetAttribLocation(program, attr.name.c_str());
        glEnableVertexAttribArray(loc);
        if (attr.dataType == ELVertexAttributeDataTypeFloat) {
            glVertexAttribPointer(loc, attr.sizeInBytes / sizeof(GLfloat), GL_FLOAT, GL_FALSE, attr.sizeInBytes, (char *)NULL + attr.offsetInBytes);
        } else if (attr.dataType == ELVertexAttributeDataTypeInt) {
            glVertexAttribPointer(loc, attr.sizeInBytes / sizeof(GLint), GL_INT, GL_FALSE, attr.sizeInBytes, (char *)NULL + attr.offsetInBytes);
        }
        vertexSize += attr.sizeInBytes;
    }
    GLenum drawType = GL_TRIANGLES;
    switch (type) {
        case ELPrimitivesTypeTriangleStrip:
            drawType = GL_TRIANGLE_STRIP;
            break;
        case ELPrimitivesTypeLine:
            drawType = GL_LINE;
            break;
        case ELPrimitivesTypeLineStrip:
            drawType = GL_LINE_STRIP;
            break;
        case ELPrimitivesTypePoint:
            drawType = GL_POINT;
            break;
    }
    glDrawArrays(drawType, 0, vertexBuffer->size() / vertexSize);
}

void ELRenderer::drawIndexedPrimitives(ELPrimitivesType type, ELVertexBufferPtr vertexBuffer, ELVertexBufferPtr indexBuffer) {

}

