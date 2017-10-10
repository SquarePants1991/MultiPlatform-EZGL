//
// Created by wang yang on 2017/10/10.
//

#ifndef EZGL_CONEGEOMETRYTESTS_H
#define EZGL_CONEGEOMETRYTESTS_H

#include "GeometryTestsBase.h"

class ConeGeometryTests: public GeometryTestsBase {
public:
    ConeGeometryTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    void prepareGeometry();
};


#endif //EZGL_CONEGEOMETRYTESTS_H
