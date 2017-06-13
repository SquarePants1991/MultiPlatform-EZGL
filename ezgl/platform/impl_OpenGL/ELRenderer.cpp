//
// Created by wangyang on 2017/5/24.
//

#include "../ELRenderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include "../types/EZGLTypes.h"
#include "../ELPlatform.h"

GLuint beginDraw(ELRendererPtr renderer, ELCrossPlatformObject *vertexBuffer, GLuint program, bool *vaoExists) {
    char buffer[255];
    sprintf(buffer, "program_%d_vao", program);

    *vaoExists = vertexBuffer->__crossplatformIntExist(buffer);
    GLuint vao;
    if (!(*vaoExists)) {
        glGenVertexArrays(1, &vao);
        vertexBuffer->__crossplatformAttach(buffer, (ELInt)vao);
    } else {
        vao = vertexBuffer->__crossplatformFetchInt(buffer);
    }
    return vao;
}

void setupBlend(bool enabled, GLenum srcFactor, GLenum dstFactor) {
    static bool _enabled = false;
    static int _srcFactor = -1;
    static int _dstFactor = -1;
    if (enabled != _enabled) {
        _enabled = enabled;
        if (enabled) {
            glEnable(GL_BLEND);
        } else {
            glDisable(GL_BLEND);
        }
    }
    if (enabled) {
        if (dstFactor != _dstFactor || srcFactor != _srcFactor) {
            _srcFactor = srcFactor;
            _dstFactor = dstFactor;
            glBlendFunc(srcFactor, dstFactor);
        }
    }
}

ELRendererPtr ELRenderer::init(ELRenderPassPtr renderPass, ELRenderPiplinePtr pipline) {
    self->renderPass = renderPass;
    self->pipline = pipline;
    // init blend vars
    self->isBlendEnabled = false;
    self->srcBlendFactor = ELBlendFactorUndef;
    self->dstBlendFactor = ELBlendFactorUndef;
    return self;
}

void ELRenderer::prepare() {
    glBindFramebuffer(GL_FRAMEBUFFER, self->renderPass->renderTarget->__crossplatformFetchInt("framebuffer"));
    glViewport(0, 0, self->renderPass->renderTarget->size.x, self->renderPass->renderTarget->size.y);
    if (renderPass->config.loadAction == ELRenderPassLoadActionClear) {
        ELVector4 clearColor = renderPass->config.clearColor;
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        GLbitfield clearMask = renderPass->renderTarget->colorBufferEnabled ? GL_COLOR_BUFFER_BIT : 0;
        clearMask |= renderPass->renderTarget->depthBufferEnabled ? GL_DEPTH_BUFFER_BIT : 0;
        clearMask |= renderPass->renderTarget->stencilBufferEnabled ? GL_STENCIL_BUFFER_BIT : 0;
        glClear(clearMask);
    }

    GLuint program = this->pipline->__crossplatformFetchInt("program");
    this->pipline->clearState();
    glUseProgram(program);

    // Blend Setup
    static GLenum glBlendFactors[] = {
            GL_ONE,
            GL_ZERO,
            GL_SRC_ALPHA,
            GL_SRC_COLOR,
            GL_DST_ALPHA,
            GL_DST_COLOR,
            GL_ONE_MINUS_SRC_ALPHA,
            GL_ONE_MINUS_SRC_COLOR,
            GL_ONE_MINUS_DST_ALPHA,
            GL_ONE_MINUS_DST_COLOR,
    };
    setupBlend(self->isBlendEnabled, glBlendFactors[self->srcBlendFactor], glBlendFactors[self->dstBlendFactor]);
}

void ELRenderer::endRender() {

}

void ELRenderer::drawPrimitives(ELPrimitivesType type, ELCompositionVertexBufferPtr vertexBuffer) {
    GLuint program = self->pipline->__crossplatformFetchInt("program");
    bool vaoExists;
    GLuint vao = beginDraw(self, vertexBuffer.get(), program, &vaoExists);
    ELVertexBufferPtr firstBuffer = vertexBuffer->buffers.at(0);
    bool useIndex = false;
    if (!vaoExists) {
        glBindVertexArray(vao);
        for (auto iter = vertexBuffer->buffers.begin(); iter != vertexBuffer->buffers.end(); ++iter) {
            ELVertexBufferPtr subBuffer = *iter;
            ELInt vertexSize = subBuffer->vertexSizeInBytes;
            GLuint vbo = subBuffer->__crossplatformFetchInt("vbo");
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            if (subBuffer->useIndex) {
                GLuint ibo = subBuffer->__crossplatformFetchInt("ibo");
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
                useIndex = true;
            }

            for (int i = 0; i < subBuffer->attributes.size(); ++i) {
                ELVertexAttribute attr = subBuffer->attributes.at(i);
                GLuint loc = glGetAttribLocation(program, attr.name.c_str());
                glEnableVertexAttribArray(loc);
                if (attr.dataType == ELVertexAttributeDataTypeFloat) {
                    glVertexAttribPointer(loc, attr.sizeInBytes / sizeof(GLfloat), GL_FLOAT, GL_FALSE, vertexSize, (char *)NULL + attr.offsetInBytes);
                } else if (attr.dataType == ELVertexAttributeDataTypeInt) {
                    glVertexAttribPointer(loc, attr.sizeInBytes / sizeof(GLint), GL_INT, GL_FALSE, vertexSize, (char *)NULL + attr.offsetInBytes);
                }
            }
        }
        glBindVertexArray(0);
    }

    GLenum drawType = GL_TRIANGLES;
    switch (type) {
        case ELPrimitivesTypeTriangleStrip:
            drawType = GL_TRIANGLE_STRIP;
            break;
        case ELPrimitivesTypeLine:
            drawType = GL_LINES;
            break;
        case ELPrimitivesTypeLineStrip:
            drawType = GL_LINE_STRIP;
            break;
        case ELPrimitivesTypePoint:
            drawType = GL_POINTS;
            break;
    }
    glBindVertexArray(vao);
    if (useIndex) {
        glDrawElements(drawType, vertexBuffer->vertexCount(), GL_UNSIGNED_INT, NULL);
    } else {
        glDrawArrays(drawType, 0, vertexBuffer->vertexCount());
    }
}

void ELRenderer::drawPrimitives(ELPrimitivesType type, ELVertexBufferPtr vertexBuffer) {
    if (vertexBuffer->attributes.size() == 0) {
        return;
    }
    ELInt  vertexSize = vertexBuffer->vertexSizeInBytes;
    GLuint program = self->pipline->__crossplatformFetchInt("program");
    bool vaoExists;
    GLuint vao = beginDraw(self, vertexBuffer.get(), program, &vaoExists);
    if (!vaoExists) {
        glBindVertexArray(vao);
        GLuint vbo = vertexBuffer->__crossplatformFetchInt("vbo");
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        if (vertexBuffer->useIndex) {
            GLuint ibo = vertexBuffer->__crossplatformFetchInt("ibo");
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        }

        for (int i = 0; i < vertexBuffer->attributes.size(); ++i) {
            ELVertexAttribute attr = vertexBuffer->attributes.at(i);
            GLuint loc = glGetAttribLocation(program, attr.name.c_str());
            glEnableVertexAttribArray(loc);
            if (attr.dataType == ELVertexAttributeDataTypeFloat) {
                glVertexAttribPointer(loc, attr.sizeInBytes / sizeof(GLfloat), GL_FLOAT, GL_FALSE, vertexSize, (char *)NULL + attr.offsetInBytes);
            } else if (attr.dataType == ELVertexAttributeDataTypeInt) {
                glVertexAttribPointer(loc, attr.sizeInBytes / sizeof(GLint), GL_INT, GL_FALSE, vertexSize, (char *)NULL + attr.offsetInBytes);
            }
        }
        glBindVertexArray(0);
    }

    GLenum drawType = GL_TRIANGLES;
    switch (type) {
        case ELPrimitivesTypeTriangleStrip:
            drawType = GL_TRIANGLE_STRIP;
            break;
        case ELPrimitivesTypeLine:
            drawType = GL_LINES;
            break;
        case ELPrimitivesTypeLineStrip:
            drawType = GL_LINE_STRIP;
            break;
        case ELPrimitivesTypePoint:
            drawType = GL_POINTS;
            break;
    }
    glBindVertexArray(vao);
    if (vertexBuffer->useIndex) {
        glDrawElements(drawType, vertexBuffer->vertexCount(), GL_UNSIGNED_INT, NULL);
    } else {
        glDrawArrays(drawType, 0, vertexBuffer->vertexCount());
    }

}

void ELRenderer::enableBlend() {
    if (self->isBlendEnabled == false) {
        self->isBlendEnabled = true;
    }
}

void ELRenderer::disableBlend() {
    if (self->isBlendEnabled == true) {
        self->isBlendEnabled = false;
    }
}
void ELRenderer::setBlendMode(ELBlendFactor srcFactor, ELBlendFactor dstFactor) {
    self->srcBlendFactor = srcFactor;
    self->dstBlendFactor = dstFactor;
}
