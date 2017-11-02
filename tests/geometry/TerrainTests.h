//
// Created by wang yang on 2017/11/2.
//

#ifndef EZGL_TERRAINTESTS_H
#define EZGL_TERRAINTESTS_H


#include "GeometryTestsBase.h"

class TerrainTests: public GeometryTestsBase {
public:
    TerrainTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    void prepareGeometry();
    virtual void preprocessMVP(ELMatrix4 *projection, ELMatrix4 *view, ELMatrix4 *model, ELFloat deltaTime);
};


#endif //EZGL_TERRAINTESTS_H
