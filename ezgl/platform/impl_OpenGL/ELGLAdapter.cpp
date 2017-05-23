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

}