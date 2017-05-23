//
// Created by wang yang on 2017/5/23.
//

#ifndef EZGL_ELGLADAPTER_H
#define EZGL_ELGLADAPTER_H

#include <GLFW/glfw3.h>

class ELGLAdapter {
public:
    GLFWwindow *window;
    static ELGLAdapter *defaultAdapter();
    void setup(GLFWwindow *window);
private:
    static ELGLAdapter *_defaultAdapter;
};


#endif //EZGL_ELGLADAPTER_H
