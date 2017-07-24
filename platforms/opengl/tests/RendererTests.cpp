//
// Created by wang yang on 2017/7/12.
//

#include "TestFramework.cpp"

#include "BaseRendererTests.h"
#include "LambertPhongRendererTests.h"

void prepare() {

}

void registerScenes() {
    RegisterTestScene(BaseRendererTests, "基础渲染器测试");
    RegisterTestScene(LambertPhongRendererTests, "Lambert Phong渲染器测试");
}
