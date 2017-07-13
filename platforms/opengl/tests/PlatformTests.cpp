//
// Created by wang yang on 2017/7/12.
//


#include "TestFramework.cpp"

#include "BasicFlowTests.h"
#include "MultiBufferTests.h"
#include "IndexBufferTests.h"
#include "BlendModeTests.h"
#include "AlphaTestTests.h"
#include "StencilTestTests.h"
#include "DepthTestTests.h"

void prepare() {

}

void registerScenes() {
    RegisterTestScene(BasicFlowTests, "基本渲染流程测试&渲染到纹理");
    RegisterTestScene(MultiBufferTests, "使用多Buffer渲染单个物体");
    RegisterTestScene(IndexBufferTests, "使用索引Buffer渲染单个物体");
    RegisterTestScene(BlendModeTests, "Blend Mode测试");
    RegisterTestScene(AlphaTestTests, "Alpha Test测试");
    RegisterTestScene(StencilTestTests, "Stencil Test测试");
    RegisterTestScene(DepthTestTests, "Depth Test测试");

//    RegisterTestScene(BasicRendererTests, "基础渲染器测试");
}