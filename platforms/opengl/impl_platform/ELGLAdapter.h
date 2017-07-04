//
// Created by wang yang on 2017/5/23.
//

#ifndef EZGL_ELGLADAPTER_H
#define EZGL_ELGLADAPTER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "platform/types/EZGLTypes.h"

class ELGLAdapter {
public:
    GLFWwindow *window;
    static ELGLAdapter *defaultAdapter();
    void setup(GLFWwindow *window);

    GLint defaultFramebuffer;
    ELVector2 defaultFBSize;
    bool enableDepthBuffer;
    bool enableStencilBuffer;
    ELPixelFormat defaultPixelFormat;
private:
    static ELGLAdapter *_defaultAdapter;
};


#endif //EZGL_ELGLADAPTER_H
