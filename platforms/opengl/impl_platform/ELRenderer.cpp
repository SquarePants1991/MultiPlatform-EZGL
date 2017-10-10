//
// Created by wangyang on 2017/5/24.
//

#include "platform/ELRenderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include "platform/types/EZGLTypes.h"
#include "platform/ELPlatform.h"
#include "platform/ELRenderPass.h"

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

inline void setupBlend(bool enabled, GLenum srcFactor, GLenum dstFactor) {
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

inline void setupDepthTest(bool enabled) {
    static bool _enabled = false;
    if (enabled != _enabled) {
        _enabled = enabled;
        if (enabled) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
    }
}

inline void setupDepthFunc(ELTest testType) {
    static ELTest _testType = ELTestNone;
    if (testType != _testType) {
        _testType = testType;
        static GLenum GLTests[] = {
                GL_NEVER,
                GL_ALWAYS,
                GL_LESS,
                GL_GREATER,
                GL_EQUAL,
                GL_LEQUAL,
                GL_GEQUAL,
                GL_NOTEQUAL,
        };
        glDepthFunc(GLTests[testType]);
    }
}

inline void setupDepthWrite(bool enabled) {
    static bool _enabled = false;
    if (enabled != _enabled) {
        _enabled = enabled;
        if (enabled) {
            glDepthMask(GL_TRUE);
        } else {
            glDepthMask(GL_FALSE);
        }
    }
}

inline void setupCullFace(bool enabled, ELCullFaceType cullfaceType, ELFrontFaceType frontFaceType) {
    static bool _enabled = false;
    if (enabled != _enabled) {
        _enabled = enabled;
        if (enabled) {
            glEnable(GL_CULL_FACE);
        } else {
            glDisable(GL_CULL_FACE);
        }
    }
    if (_enabled) {
        if (frontFaceType == ELFrontFaceTypeCCW) {
            glFrontFace(GL_CCW);
        } else {
            glFrontFace(GL_CW);
        }
        if (cullfaceType == ELCullFaceTypeFront) {
            glCullFace(GL_FRONT);
        } else {
            glCullFace(GL_BACK);
        }
    }
}

inline void setupStencil(bool enabled, ELInt stencilMask, ELStencilOpArgs opArgs, ELStencilFuncArgs funcArgs) {
    static bool _enabled = false;
    static ELInt _stencilMask = 0xff;
    static ELStencilOpArgs _stencilOpArgs = { ELStencilOpNone, ELStencilOpNone, ELStencilOpNone };
    static ELStencilFuncArgs _funcArgs = { ELTestNone, 0 };
    if (enabled != _enabled) {
        _enabled = enabled;
        if (enabled) {
            glEnable(GL_STENCIL_TEST);
        } else {
            glDisable(GL_STENCIL_TEST);
        }
    }

    static GLenum GLTests[] = {
        GL_NEVER,
        GL_ALWAYS,
        GL_LESS,
        GL_GREATER,
        GL_EQUAL,
        GL_LEQUAL,
        GL_GEQUAL,
        GL_NOTEQUAL,
    };

    static GLenum GLStencilOps[] = {
        GL_KEEP,
        GL_ZERO,
        GL_INCR,
        GL_INCR_WRAP,
        GL_DECR,
        GL_DECR_WRAP,
        GL_INVERT,
        GL_REPLACE,
    };

    if (_enabled) {
        if (stencilMask != _stencilMask) {
            _stencilMask = stencilMask;
            glStencilMask(_stencilMask);
        }
        if (ELStencilOpArgsEqual(opArgs, _stencilOpArgs) == false) {
            _stencilOpArgs = opArgs;
            glStencilOp(GLStencilOps[_stencilOpArgs.stencilTestFailed], GLStencilOps[_stencilOpArgs.depthTestFailed], GLStencilOps[_stencilOpArgs.success]);
        }
        if (ELStencilFuncArgsEqual(funcArgs, _funcArgs) == false) {
            _funcArgs = funcArgs;
            glStencilFunc(GLTests[_funcArgs.testType], _funcArgs.ref, _funcArgs.mask);
        }
    }
}

ELRendererPtr ELRenderer::init(ELRenderPassPtr renderPass, ELRenderPiplinePtr pipline) {
    selv->renderPass = renderPass;
    selv->pipline = pipline;
    // init blend vars
    selv->isBlendEnabled = false;
    selv->srcBlendFactor = ELBlendFactorUndef;
    selv->dstBlendFactor = ELBlendFactorUndef;
    // init depth test vars
    selv->isDepthTestEnabled = false;
    selv->depthFunc = ELTestLessEqual;
    // init depth mask vars
    selv->isDepthWriteEnabled = false;
    // init stencil mask vars
    selv->isStencilTestEnabled = false;
    selv->stencilMask = 0xff;
    selv->stencilOpArgs = ELStencilOpArgsMake(ELStencilOpKeep, ELStencilOpKeep, ELStencilOpReplace);
    selv->stencilFuncArgs = ELStencilFuncArgsMake(ELTestAlways, 0, 0xFF);

    // cull face
    selv->isCullfaceEnabled = false;
    selv->cullFaceType = ELCullFaceTypeBack;
    selv->frontFaceType = ELFrontFaceTypeCCW;
    return selv;
}

void ELRenderer::prepare() {
    // Depth Write Setup
    setupDepthWrite(selv->isDepthWriteEnabled);


    glBindFramebuffer(GL_FRAMEBUFFER, selv->renderPass->renderTarget->__crossplatformFetchInt("framebuffer"));
    glViewport(0, 0, selv->renderPass->renderTarget->size.x, selv->renderPass->renderTarget->size.y);
    if (renderPass->config.loadAction == ELRenderPassLoadActionClear) {
        ELVector4 clearColor = renderPass->config.clearColor;
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        if (renderPass->renderTarget->depthBufferEnabled) {
            glClearDepth(renderPass->config.clearDepth);
        }
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
    setupBlend(selv->isBlendEnabled, glBlendFactors[selv->srcBlendFactor], glBlendFactors[selv->dstBlendFactor]);

    // Depth Test Setup
    setupDepthTest(selv->isDepthTestEnabled);
    setupDepthFunc(selv->depthFunc);

    setupStencil(selv->isStencilTestEnabled, selv->stencilMask, selv->stencilOpArgs, selv->stencilFuncArgs);
}

void ELRenderer::endRender() {

}

void ELRenderer::drawPrimitives(ELPrimitivesType type, ELCompositionVertexBufferPtr vertexBuffer) {
    GLuint program = selv->pipline->__crossplatformFetchInt("program");
    bool vaoExists;
    GLuint vao = beginDraw(selv, vertexBuffer.get(), program, &vaoExists);
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
    GLuint program = selv->pipline->__crossplatformFetchInt("program");
    bool vaoExists;
    GLuint vao = beginDraw(selv, vertexBuffer.get(), program, &vaoExists);
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
    if (selv->isBlendEnabled == false) {
        selv->isBlendEnabled = true;
    }
}

void ELRenderer::disableBlend() {
    if (selv->isBlendEnabled == true) {
        selv->isBlendEnabled = false;
    }
}
void ELRenderer::setBlendMode(ELBlendFactor srcFactor, ELBlendFactor dstFactor) {
    selv->srcBlendFactor = srcFactor;
    selv->dstBlendFactor = dstFactor;
}

void ELRenderer::enableDepthTest() {
    selv->isDepthTestEnabled = true;
    selv->isDepthWriteEnabled = true;
    setupDepthTest(selv->isDepthTestEnabled);
    setupDepthWrite(selv->isDepthWriteEnabled);
}

void ELRenderer::disableDepthTest() {
    selv->isDepthTestEnabled = false;
    setupDepthTest(selv->isDepthTestEnabled);
}

void ELRenderer::setDepthFunc(ELTest testType) {
    selv->depthFunc = testType;
    setupDepthFunc(testType);
}

void ELRenderer::enableDepthWrite() {
    selv->isDepthWriteEnabled = true;
    setupDepthWrite(selv->isDepthWriteEnabled);
}

void ELRenderer::enableStencilTest() {
    selv->isStencilTestEnabled = true;
    setupStencil(selv->isStencilTestEnabled, selv->stencilMask, selv->stencilOpArgs, selv->stencilFuncArgs);
}

void ELRenderer::disableStencilTest() {
    selv->isStencilTestEnabled = false;
    setupStencil(selv->isStencilTestEnabled, selv->stencilMask, selv->stencilOpArgs, selv->stencilFuncArgs);
}

void ELRenderer::setStencilFunc(ELTest testType, ELInt ref, ELInt mask) {
    selv->stencilFuncArgs = ELStencilFuncArgsMake(testType, ref, mask);
    setupStencil(selv->isStencilTestEnabled, selv->stencilMask, selv->stencilOpArgs, selv->stencilFuncArgs);
}

void ELRenderer::setStencilOperations(ELStencilOp stFailed, ELStencilOp dpFailed, ELStencilOp allSuccess) {
    selv->stencilOpArgs = ELStencilOpArgsMake(stFailed, dpFailed, allSuccess);
    setupStencil(selv->isStencilTestEnabled, selv->stencilMask, selv->stencilOpArgs, selv->stencilFuncArgs);
}

void ELRenderer::setStencilMask(ELInt mask) {
    selv->stencilMask = mask;
    setupStencil(selv->isStencilTestEnabled, selv->stencilMask, selv->stencilOpArgs, selv->stencilFuncArgs);
}

void ELRenderer::disableDepthWrite() {
    selv->isDepthWriteEnabled = false;
    setupDepthWrite(selv->isDepthWriteEnabled);
}

void ELRenderer::enableCullFace() {
    selv->isCullfaceEnabled = true;
    setupCullFace(isCullfaceEnabled, cullFaceType, frontFaceType);
}

void ELRenderer::disableCullFace() {
    selv->isCullfaceEnabled = false;
    setupCullFace(isCullfaceEnabled, cullFaceType, frontFaceType);
}

void ELRenderer::setCullFaceType(ELCullFaceType cullfaceType) {
    selv->cullFaceType = cullfaceType;
    setupCullFace(isCullfaceEnabled, cullFaceType, frontFaceType);
}

void ELRenderer::setFrontFaceType(ELFrontFaceType frontFaceType) {
    selv->frontFaceType = frontFaceType;
    setupCullFace(isCullfaceEnabled, cullFaceType, frontFaceType);
}
