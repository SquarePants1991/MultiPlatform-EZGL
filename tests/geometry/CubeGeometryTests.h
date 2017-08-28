//
// Created by wang yang on 2017/8/24.
//

#ifndef EZGL_CUBEGEOMETRYTESTS_H
#define EZGL_CUBEGEOMETRYTESTS_H

#include "GeometryTestsBase.h"

class CubeGeometryTests: public GeometryTestsBase {
public:
    CubeGeometryTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    void prepareGeometry();
};


#endif //EZGL_CUBEGEOMETRYTESTS_H
