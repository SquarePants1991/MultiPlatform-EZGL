//
// Created by wang yang on 2017/8/23.
//

#include "GeometryTestsBase.h"
#include "geometry/simple/ELCubeGeometry.h"

GeometryTestsBase::GeometryTestsBase(std::map<std::string, ELRenderPiplinePtr> piplines) {
    ELRenderPassConfig config = ELRenderPassConfigDefault();
    config.clearColor = ELVector4Make(0.1, 0.1, 0.1, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();
    lambertPhongRenderer = ELLambertPhongRenderer::alloc()->init(config, defaultRenderTarget);


    std::string imagePath = ELAssets::shared()->findFile("texture.jpg");
    diffuseTexture = ELTexture::alloc()->init(imagePath);
}

void GeometryTestsBase::update(ELFloat deltaTime) {
    static float angle = 0.0;
    angle += 0.01;

    ELVector3 cameraPos = ELVector3Make(0.0, 2, 2);

    ELMatrix4 projection = ELMatrix4MakePerspective(90.0 * M_PI / 180.0, 640 / 480.0, 0.1, 1000);
    ELMatrix4 view = ELMatrix4MakeLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 0, 0, 0, 1, 0);
    ELMatrix4 model = ELMatrix4MakeRotation(angle, 0, 1, 0);

    preprocessMVP(&projection, &view, &model, deltaTime);

    bool canInvert;
    ELMatrix4 normalMatrix = ELMatrix4Invert(model, &canInvert);
    normalMatrix = ELMatrix4Transpose(normalMatrix);

    ELLightInfo light[1];
    light[0].lightType = ELLightTypeDirect;
    light[0].color = ELVector3Make(1.0, 1.0, 1.0);
    light[0].indensity = 1.0;
    light[0].pose = ELVector3Make(1,-1,1);


    ELLambertPhongMaterial material;
    material.diffuseColor = ELVector3Make(1.0, 1.0, 1.0);
    material.useDiffuseMap = false;
    material.ambientColor = ELVector3Make(0.2, 0.2, 0.2);
    material.specularColor = ELVector3Make(1.0, 1.0, 1.0);
    material.specularIndensity = 1.0;
    material.smoothness = 300;


    lambertPhongRenderer->beginDraw();

    for (auto iter = geometries.begin(); iter != geometries.end(); ++iter) {
        ELGeometryPtr geometry = *iter;
        std::vector<ELVertexBufferPtr> vertexBuffers = geometry->vertextBuffers();

        lambertPhongRenderer->setLights(light, sizeof(light) / sizeof(ELLightInfo));
        lambertPhongRenderer->setCameraPosition(cameraPos);
        lambertPhongRenderer->setMaterial(material);
        lambertPhongRenderer->setDiffuseMap(diffuseTexture);
        lambertPhongRenderer->setModelMatrix(model);
        lambertPhongRenderer->setNormalMatrix(normalMatrix);
        lambertPhongRenderer->setViewMatrix(view);
        lambertPhongRenderer->setProjectionMatrix(projection);

        for (int index = 0; index < vertexBuffers.size(); ++index) {
            ELPrimitivesType primitivesType = geometry->primitivesTypeForVertexBuffer(index);
            ELVertexBufferPtr vertexBuffer = vertexBuffers[index];
            lambertPhongRenderer->setNormalMapEnable(false);
            lambertPhongRenderer->setVertexBuffer(vertexBuffer);

            lambertPhongRenderer->draw(primitivesType);
        }
    }

    lambertPhongRenderer->commitDraw();
}