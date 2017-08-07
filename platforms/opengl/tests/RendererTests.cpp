//
// Created by wang yang on 2017/7/12.
//

#include "TestFramework.cpp"

#include "BaseRendererTests.h"
#include "LambertPhongRendererTests.h"
#include "LambertBlinnRendererTests.h"
#include "LambertPhongNormalMapTests.h"
#include "LambertBlinnNormalMapTests.h"
#include "LambertBlinnDecalRendererTests.h"

void prepare() {

}

void registerScenes() {
    RegisterTestScene(BaseRendererTests, "基础渲染器测试");
    RegisterTestScene(LambertPhongRendererTests, "Lambert Phong渲染器测试");
    RegisterTestScene(LambertPhongNormalMapTests, "Lambert Phong Normal Map测试");
    RegisterTestScene(LambertBlinnRendererTests, "Lambert Blinn渲染器测试");
    RegisterTestScene(LambertBlinnNormalMapTests, "Lambert Blinn Normal Map测试");
    RegisterTestScene(LambertBlinnDecalRendererTests, "Lambert Blinn 贴花测试");
}
