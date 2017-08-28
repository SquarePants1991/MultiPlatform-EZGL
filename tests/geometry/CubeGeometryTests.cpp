//
// Created by wang yang on 2017/8/24.
//

#include "CubeGeometryTests.h"
#include "geometry/simple/ELCubeGeometry.h"

CubeGeometryTests::CubeGeometryTests(std::map<std::string, ELRenderPiplinePtr> piplines): GeometryTestsBase(piplines) {
    prepareGeometry();
}

void CubeGeometryTests::prepareGeometry() {
    ELCubeGeometryPtr cubeGeometry = ELCubeGeometry::alloc()->init(ELVector3Make(1, 1, 1));
    geometries.push_back(std::dynamic_pointer_cast<ELGeometry>(cubeGeometry));
}