//
// Created by wang yang on 2017/9/14.
//

#include "SkyBoxTests.h"
#include "geometry/simple/ELCubeGeometry.h"


SkyBoxTests::SkyBoxTests(std::map<std::string, ELRenderPiplinePtr> piplines) {
    ELRenderPassConfig config = ELRenderPassConfigDefault();
    config.clearColor = ELVector4Make(0.1, 0.1, 0.1, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();
    renderer = ELSkyBoxRenderer::alloc()->init(config, defaultRenderTarget);

    std::vector<std::string> imagePaths;
    char filename[255];
    for (int i = 0; i < 6; ++i) {
        sprintf(filename, "skybox-%d.jpg", i + 1);
        std::string imagePath = ELAssets::shared()->findFile(filename);
        imagePaths.push_back(imagePath);
    }

    skyBoxMap = ELTexture::alloc()->init(imagePaths);

    ELCubeGeometryPtr cubeGeometry = ELCubeGeometry::alloc()->init(ELVector3Make(9000, 9000, 9000));
    geometries.push_back(std::dynamic_pointer_cast<ELGeometry>(cubeGeometry));
}

void SkyBoxTests::update(ELFloat deltaTime) {
    static float angle = 0.0;
    angle += 0.01;

    ELVector3 cameraPos = ELVector3Make(sin(angle) * 3, 0, cos(angle) * 3);

    ELMatrix4 projection = ELMatrix4MakePerspective(50.0 * M_PI / 180.0, 640 / 480.0, 0.1, 10000);
    ELMatrix4 view = ELMatrix4MakeLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 1, 0, 0, 1, 0);
    ELMatrix4 model = ELMatrix4MakeRotation(0, 1, 0, 0);

    bool canInvert;
    ELMatrix4 normalMatrix = ELMatrix4Invert(model, &canInvert);
    normalMatrix = ELMatrix4Transpose(normalMatrix);

    renderer->beginDraw();

    for (auto iter = geometries.begin(); iter != geometries.end(); ++iter) {
        ELGeometryPtr geometry = *iter;
        std::vector<ELVertexBufferPtr> vertexBuffers = geometry->vertextBuffers();

        renderer->setSkyBoxCubeMap(skyBoxMap);
        renderer->setModelMatrix(model);
        renderer->setNormalMatrix(normalMatrix);
        renderer->setViewMatrix(view);
        renderer->setProjectionMatrix(projection);

        for (int index = 0; index < vertexBuffers.size(); ++index) {
            ELPrimitivesType primitivesType = geometry->primitivesTypeForVertexBuffer(index);
            ELVertexBufferPtr vertexBuffer = vertexBuffers[index];
            renderer->setNormalMapEnable(false);
            renderer->setVertexBuffer(vertexBuffer);
            renderer->renderer->setCullFaceType(ELCullFaceTypeFront);
            renderer->draw(primitivesType);
            renderer->renderer->setCullFaceType(ELCullFaceTypeBack);
        }
    }

    renderer->commitDraw();
}