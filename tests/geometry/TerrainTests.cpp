//
// Created by wang yang on 2017/11/2.
//

#include "TerrainTests.h"
#include "geometry/complex/ELTerrain.h"

#define TerrainSize 40

TerrainTests::TerrainTests(std::map<std::string, ELRenderPiplinePtr> piplines): GeometryTestsBase(piplines) {
    prepareGeometry();
}

void TerrainTests::prepareGeometry() {
    std::string filePath = ELAssets::shared()->findFile("terrain_01.jpg");
    ELTerrainPtr terrain = ELTerrain::alloc()->init(filePath, ELVector2Make(TerrainSize, TerrainSize), TerrainSize / 5);
    geometries.push_back(std::dynamic_pointer_cast<ELGeometry>(terrain));
}

void TerrainTests::preprocessMVP(ELMatrix4 *projection, ELMatrix4 *view, ELMatrix4 *model) {
    static float angle = 0;
    angle += 0.01;
    *view = ELMatrix4MakeLookAt(0, 20, 30, 0, 0, 0, 0, 1, 0);
    *model = ELMatrix4Multiply(ELMatrix4MakeRotation(angle, 0, 1, 0), ELMatrix4MakeTranslation(-TerrainSize / 2, 0, -TerrainSize / 2));
}