//
// Created by wang yang on 2017/9/8.
//

#include "CylinderGeometryTests.h"
#include "geometry/simple/ELCylinderGeometry.h"

CylinderGeometryTests::CylinderGeometryTests(std::map<std::string, ELRenderPiplinePtr> piplines): GeometryTestsBase(piplines) {
    prepareGeometry();
}

void CylinderGeometryTests::prepareGeometry() {
    ELCylinderGeometryPtr geometry = ELCylinderGeometry::alloc()->init(0.5, 1.0, 36, 36);
    geometries.push_back(std::dynamic_pointer_cast<ELGeometry>(geometry));
}