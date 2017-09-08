//
// Created by wang yang on 2017/9/8.
//

#ifndef EZGL_CYLINDERGEOMETRYTESTS_H
#define EZGL_CYLINDERGEOMETRYTESTS_H

#include "GeometryTestsBase.h"

class CylinderGeometryTests: public GeometryTestsBase {
public:
    CylinderGeometryTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    void prepareGeometry();
};


#endif //EZGL_CYLINDERGEOMETRYTESTS_H
