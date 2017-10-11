//
// Created by wang yang on 2017/10/10.
//

#include "ConeGeometryTests.h"
#include "geometry/simple/ELConeGeometry.h"

ConeGeometryTests::ConeGeometryTests(std::map<std::string, ELRenderPiplinePtr> piplines): GeometryTestsBase(piplines) {
    prepareGeometry();
}

void ConeGeometryTests::prepareGeometry() {
    ELConeGeometryPtr geometry = ELConeGeometry::alloc()->init(1.0, 2.0, 36, 1);
    geometries.push_back(std::dynamic_pointer_cast<ELGeometry>(geometry));
}