//
// Created by wang yang on 2017/8/28.
//

#ifndef EZGL_SPHEREGEOMETRYTESTS_H
#define EZGL_SPHEREGEOMETRYTESTS_H


#include "GeometryTestsBase.h"

class SphereGeometryTests: public GeometryTestsBase {
public:
    SphereGeometryTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    void prepareGeometry();
};



#endif //EZGL_SPHEREGEOMETRYTESTS_H
