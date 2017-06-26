//
// Created by wangyang on 2017/6/7.
//

#ifndef EZGL_TESTSCENE_H
#define EZGL_TESTSCENE_H

#include "ELPlatform.h"

class TestScene {
public:
    // register some piplines for tests
    std::map<std::string, ELRenderPiplinePtr> piplines;
    TestScene() {

    }
    TestScene(std::map<std::string, ELRenderPiplinePtr> piplines) {
        this->piplines = piplines;
    }
    virtual void update(ELFloat deltaTime) = 0;
};


#endif //EZGL_TESTSCENE_H
