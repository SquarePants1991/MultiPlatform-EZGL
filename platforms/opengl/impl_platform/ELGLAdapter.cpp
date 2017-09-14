//
// Created by wang yang on 2017/5/23.
//

#include "ELGLAdapter.h"


ELGLAdapter * ELGLAdapter::_defaultAdapter = NULL;

ELGLAdapter * ELGLAdapter::defaultAdapter() {
    if ( ELGLAdapter::_defaultAdapter == NULL) {
        ELGLAdapter::_defaultAdapter = new ELGLAdapter();
    }
    return _defaultAdapter;
}

void ELGLAdapter::setup(GLFWwindow *window) {
    this->window = window;
    GLint defaultFrameBuffer;
    glGetIntegerv(GL_FRAMEBUFFER, &defaultFrameBuffer);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    this->defaultFBSize = ELVector2Make(width, height);
    this->enableDepthBuffer = true;
    this->enableStencilBuffer = true;
    this->defaultPixelFormat = ELPixelFormatRGBA;

//    glEnable(GL_CULL_FACE);
}