//
// Created by wang yang on 2017/10/10.
//

#include "PlaneGeometryTests.h"
#include "geometry/simple/ELPlaneGeometry.h"

PlaneGeometryTests::PlaneGeometryTests(std::map<std::string, ELRenderPiplinePtr> piplines): GeometryTestsBase(piplines) {
    prepareGeometry();
    lambertPhongRenderer->renderer->enableCullFace();
//    lambertPhongRenderer->renderer->setCullFaceType(ELCullFaceTypeBack);
}

void PlaneGeometryTests::prepareGeometry() {
    ELPlaneGeometryPtr geometry = ELPlaneGeometry::alloc()->init(ELVector2Make(4, 4), ELVector2Make(2.0, 2.0));
    geometries.push_back(std::dynamic_pointer_cast<ELGeometry>(geometry));
}