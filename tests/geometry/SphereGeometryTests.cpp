//
// Created by wang yang on 2017/8/28.
//

#include "SphereGeometryTests.h"
#include "geometry/simple/ELSphereGeometry.h"

SphereGeometryTests::SphereGeometryTests(std::map<std::string, ELRenderPiplinePtr> piplines): GeometryTestsBase(piplines) {
    prepareGeometry();
}

void SphereGeometryTests::prepareGeometry() {
    ELSphereGeometryPtr sphereGeometry = ELSphereGeometry::alloc()->init(1.4, 40, 40);
    geometries.push_back(std::dynamic_pointer_cast<ELGeometry>(sphereGeometry));
}