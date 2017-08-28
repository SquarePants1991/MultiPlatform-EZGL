//
// Created by wang yang on 2017/8/23.
//

#include "TestFramework.cpp"

#include "CubeGeometryTests.h"
#include "SphereGeometryTests.h"

void prepare() {

}

void registerScenes() {
    RegisterTestScene(CubeGeometryTests, "Cube几何体测试");
    RegisterTestScene(SphereGeometryTests, "Sphere几何体测试");
}