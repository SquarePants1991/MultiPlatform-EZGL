//
// Created by wang yang on 2017/7/24.
//

#include <renderer/ELLambertBlinnRenderer.h>
#include "LambertBlinnRendererTests.h"
#include "sphere.h"


LambertBlinnRendererTests::LambertBlinnRendererTests(std::map<std::string, ELRenderPiplinePtr> piplines) {
    ELRenderPassConfig config = ELRenderPassConfigDefault();
    config.clearColor = ELVector4Make(0.1, 0.1, 0.1, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();
    lambertBlinnRenderer = ELLambertBlinnRenderer::alloc()->init(config, defaultRenderTarget);


    std::string imagePath = ELAssets::shared()->findFile("texture.jpg");
    diffuseTexture = ELTexture::alloc()->init(imagePath);
//    static ELFloat data[] = {
//            // X轴0.5处的平面
//            0.5, -0.5, 0.5f, 1, 0, 0, 0, 0,
//            0.5, -0.5f, -0.5f, 1, 0, 0, 0, 1,
//            0.5, 0.5f, -0.5f, 1, 0, 0, 1, 1,
//            0.5, 0.5, -0.5f, 1, 0, 0, 1, 1,
//            0.5, 0.5f, 0.5f, 1, 0, 0, 1, 0,
//            0.5, -0.5f, 0.5f, 1, 0, 0, 0, 0,
//            // X轴-0.5处的平面
//            -0.5, -0.5, 0.5f, -1, 0, 0, 0, 0,
//            -0.5, -0.5f, -0.5f, -1, 0, 0, 0, 1,
//            -0.5, 0.5f, -0.5f, -1, 0, 0, 1, 1,
//            -0.5, 0.5, -0.5f, -1, 0, 0, 1, 1,
//            -0.5, 0.5f, 0.5f, -1, 0, 0, 1, 0,
//            -0.5, -0.5f, 0.5f, -1, 0, 0, 0, 0,
//
//            -0.5, 0.5, 0.5f, 0, 1, 0, 0, 0,
//            -0.5f, 0.5, -0.5f, 0, 1, 0, 0, 1,
//            0.5f, 0.5, -0.5f, 0, 1, 0, 1, 1,
//            0.5, 0.5, -0.5f, 0, 1, 0, 1, 1,
//            0.5f, 0.5, 0.5f, 0, 1, 0, 1, 0,
//            -0.5f, 0.5, 0.5f, 0, 1, 0, 0, 0,
//            -0.5, -0.5, 0.5f, 0, -1, 0, 0, 0,
//            -0.5f, -0.5, -0.5f, 0, -1, 0, 0, 1,
//            0.5f, -0.5, -0.5f, 0, -1, 0, 1, 1,
//            0.5, -0.5, -0.5f, 0, -1, 0, 1, 1,
//            0.5f, -0.5, 0.5f, 0, -1, 0, 1, 0,
//            -0.5f, -0.5, 0.5f, 0, -1, 0, 0, 0,
//
//            -0.5, 0.5f, 0.5, 0, 0, 1, 0, 0,
//            -0.5f, -0.5f, 0.5, 0, 0, 1, 0, 1,
//            0.5f, -0.5f, 0.5, 0, 0, 1, 1, 1,
//            0.5, -0.5f, 0.5, 0, 0, 1, 1, 1,
//            0.5f, 0.5f, 0.5, 0, 0, 1, 1, 0,
//            -0.5f, 0.5f, 0.5, 0, 0, 1, 0, 0,
//            -0.5, 0.5f, -0.5, 0, 0, -1, 0, 0,
//            -0.5f, -0.5f, -0.5, 0, 0, -1, 0, 1,
//            0.5f, -0.5f, -0.5, 0, 0, -1, 1, 1,
//            0.5, -0.5f, -0.5, 0, 0, -1, 1, 1,
//            0.5f, 0.5f, -0.5, 0, 0, -1, 1, 0,
//            -0.5f, 0.5f, -0.5, 0, 0, -1, 0, 0,
//    };
//
//    cubeVertexBuffer = ELVertexBuffer::alloc()->init(data, sizeof(data), sizeof(ELFloat) * 8, ELVertexBufferTypeStatic);
//    ELVertexAttribute positionAttr;
//    positionAttr.dataType = ELVertexAttributeDataTypeFloat;
//    positionAttr.sizeInBytes = sizeof(ELFloat) * 3;
//    positionAttr.offsetInBytes = 0;
//    positionAttr.name = "v_position";
//    cubeVertexBuffer->addAttribute(positionAttr);
//    ELVertexAttribute colorAttr;
//    colorAttr.dataType = ELVertexAttributeDataTypeFloat;
//    colorAttr.sizeInBytes = sizeof(ELFloat) * 3;
//    colorAttr.offsetInBytes = sizeof(ELFloat) * 3;
//    colorAttr.name = "v_normal";
//    cubeVertexBuffer->addAttribute(colorAttr);
//    ELVertexAttribute uvAttr;
//    uvAttr.dataType = ELVertexAttributeDataTypeFloat;
//    uvAttr.sizeInBytes = sizeof(ELFloat) * 2;
//    uvAttr.offsetInBytes = sizeof(ELFloat) * 6;
//    uvAttr.name = "v_texcoord";
//    cubeVertexBuffer->addAttribute(uvAttr);

    // create sphere
    sphereVertexBuffer = ELCompositionVertexBuffer::alloc()->init();

    ELVertexBufferPtr vertexBuffer = ELVertexBuffer::alloc()->init(sphereVerts, sizeof(ELFloat) * 3 * sphereNumVerts, sizeof(ELFloat) * 3, ELVertexBufferTypeStatic);
    ELVertexAttribute positionAttr;
    positionAttr.dataType = ELVertexAttributeDataTypeFloat;
    positionAttr.sizeInBytes = sizeof(ELFloat) * 3;
    positionAttr.offsetInBytes = 0;
    positionAttr.name = "v_position";
    vertexBuffer->addAttribute(positionAttr);
    sphereVertexBuffer->appendVertexBuffer(vertexBuffer);

    ELVertexBufferPtr normalBuffer = ELVertexBuffer::alloc()->init(sphereNormals, sizeof(sphereNormals), sizeof(ELFloat) * 3, ELVertexBufferTypeStatic);
    ELVertexAttribute normalAttr;
    normalAttr.dataType = ELVertexAttributeDataTypeFloat;
    normalAttr.sizeInBytes = sizeof(ELFloat) * 3;
    normalAttr.offsetInBytes = 0;
    normalAttr.name = "v_normal";
    normalBuffer->addAttribute(normalAttr);
    sphereVertexBuffer->appendVertexBuffer(normalBuffer);

    ELVertexBufferPtr uvBuffer = ELVertexBuffer::alloc()->init(sphereTexCoords, sizeof(sphereTexCoords), sizeof(ELFloat) * 2, ELVertexBufferTypeStatic);
    ELVertexAttribute uvAttr;
    uvAttr.dataType = ELVertexAttributeDataTypeFloat;
    uvAttr.sizeInBytes = sizeof(ELFloat) * 2;
    uvAttr.offsetInBytes = 0;
    uvAttr.name = "v_texcoord";
    uvBuffer->addAttribute(uvAttr);
    sphereVertexBuffer->appendVertexBuffer(uvBuffer);
}

void LambertBlinnRendererTests::update(ELFloat deltaTime) {
    static float angle = 0.0;
    angle += 0.01;

    ELMatrix4 projection = ELMatrix4MakePerspective(90.0 * M_PI / 180.0, 640 / 480.0, 0.1, 1000);
    ELMatrix4 view = ELMatrix4MakeLookAt(0, 0, 1.1, 0, 0, 0, 0, 1, 0);
    ELMatrix4 model = ELMatrix4MakeRotation(0, 1, 1, 1);

    bool canInvert;
    ELMatrix4 normalMatrix = ELMatrix4Invert(model, &canInvert);
    normalMatrix = ELMatrix4Transpose(normalMatrix);

    ELLightInfo light[2];
    light[0].lightType = ELLightTypePoint;
    light[0].color = ELVector3Make(1.0, 1.0, 1.0);
    light[0].indensity = 0.6;
    light[0].pose = ELVector3Make(3,3,3);

    light[1].lightType = ELLightTypeDirect;
    light[1].color = ELVector3Make(1.0, 0.0, 1.0);
    light[1].indensity = 0.1;
    light[1].pose = ELVector3Make(0,1,0);


    ELLambertPhongMaterial material;
    material.diffuseColor = ELVector3Make(0.0, 0.0, 1.0);
    material.useDiffuseMap = false;
    material.ambientColor = ELVector3Make(0.1, 0.1, 0.1);
    material.specularColor = ELVector3Make(1.0, 1.0, 1.0);
    material.specularIndensity = 1.0;
    material.smoothness = 300;


    lambertBlinnRenderer->beginDraw();

    lambertBlinnRenderer->setNormalMapEnable(false);
    lambertBlinnRenderer->setVertexBuffer(sphereVertexBuffer);
    lambertBlinnRenderer->setLights(light, sizeof(light) / sizeof(ELLightInfo));
    lambertBlinnRenderer->setCameraPosition(ELVector3Make(0, 0, 1.1));
    lambertBlinnRenderer->setMaterial(material);
    lambertBlinnRenderer->setDiffuseMap(diffuseTexture);
    lambertBlinnRenderer->setModelMatrix(model);
    lambertBlinnRenderer->setNormalMatrix(normalMatrix);
    lambertBlinnRenderer->setViewMatrix(view);
    lambertBlinnRenderer->setProjectionMatrix(projection);
    lambertBlinnRenderer->draw(ELPrimitivesTypeTriangle);

    lambertBlinnRenderer->commitDraw();
}