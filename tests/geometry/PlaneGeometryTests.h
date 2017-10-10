//
// Created by wang yang on 2017/10/10.
//

#ifndef EZGL_PLANEGEOMETRYTESTS_H
#define EZGL_PLANEGEOMETRYTESTS_H

#include "GeometryTestsBase.h"

class PlaneGeometryTests: public GeometryTestsBase {
public:
    PlaneGeometryTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    void prepareGeometry();
};


#endif //EZGL_PLANEGEOMETRYTESTS_H
