//
// Created by wang yang on 2017/8/23.
//

#include "TestFramework.cpp"

#include "CubeGeometryTests.h"
#include "SphereGeometryTests.h"
#include "CylinderGeometryTests.h"
#include "SkyBoxTests.h"

void prepare() {

}

void registerScenes() {
    RegisterTestScene(CubeGeometryTests, "Cube几何体测试");
    RegisterTestScene(SphereGeometryTests, "Sphere几何体测试");
    RegisterTestScene(CylinderGeometryTests, "Cylinder几何体测试");
    RegisterTestScene(SkyBoxTests, "SkyBox测试");
}