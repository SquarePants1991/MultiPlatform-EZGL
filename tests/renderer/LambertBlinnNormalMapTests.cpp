//
// Created by wang yang on 2017/7/24.
//

#include <renderer/ELlambertBlinnRenderer.h>
#include "LambertBlinnNormalMapTests.h"
#include "cube.h"


void LambertBlinnNormalMapTests::update(ELFloat deltaTime) {
    static float angle = 0.0;
    angle += 0.01;

    ELMatrix4 projection = ELMatrix4MakePerspective(90.0 * M_PI / 180.0, 640 / 480.0, 0.1, 1000);
    ELMatrix4 view = ELMatrix4MakeLookAt(0, 0, 2.1, 0, 0, 0, 0, 1, 0);
    ELMatrix4 model = ELMatrix4MakeRotation(angle, 1, 1, 1);

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
    material.useDiffuseMap = true;
    material.ambientColor = ELVector3Make(0.1, 0.1, 0.1);
    material.specularColor = ELVector3Make(1.0, 1.0, 1.0);
    material.specularIndensity = 1.0;
    material.smoothness = 30;


    lambertBlinnRenderer->beginDraw();

    lambertBlinnRenderer->setNormalMap(normalTexture);
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

LambertBlinnNormalMapTests::LambertBlinnNormalMapTests(std::map<std::string, ELRenderPiplinePtr> piplines) {
    ELRenderPassConfig config = ELRenderPassConfigDefault();
    config.clearColor = ELVector4Make(0.1, 0.1, 0.1, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();
    lambertBlinnRenderer = ELLambertBlinnRenderer::alloc()->init(config, defaultRenderTarget);


    std::string imagePath = ELAssets::shared()->findFile("texture.jpg");
    diffuseTexture = ELTexture::alloc()->init(imagePath);

    std::string normalImagePath = ELAssets::shared()->findFile("texture_nrm.png");
    normalTexture = ELTexture::alloc()->init(normalImagePath);

    // create sphere
    sphereVertexBuffer = ELCompositionVertexBuffer::alloc()->init();

    ELVertexBufferPtr vertexBuffer = ELVertexBuffer::alloc()->init(cubeVerts, sizeof(cubeVerts), sizeof(ELFloat) * 3, ELVertexBufferTypeStatic);
    ELVertexAttribute positionAttr;
    positionAttr.dataType = ELVertexAttributeDataTypeFloat;
    positionAttr.sizeInBytes = sizeof(ELFloat) * 3;
    positionAttr.offsetInBytes = 0;
    positionAttr.name = "v_position";
    vertexBuffer->addAttribute(positionAttr);
    sphereVertexBuffer->appendVertexBuffer(vertexBuffer);

    ELVertexBufferPtr normalBuffer = ELVertexBuffer::alloc()->init(cubeNormals, sizeof(cubeNormals), sizeof(ELFloat) * 3, ELVertexBufferTypeStatic);
    ELVertexAttribute normalAttr;
    normalAttr.dataType = ELVertexAttributeDataTypeFloat;
    normalAttr.sizeInBytes = sizeof(ELFloat) * 3;
    normalAttr.offsetInBytes = 0;
    normalAttr.name = "v_normal";
    normalBuffer->addAttribute(normalAttr);
    sphereVertexBuffer->appendVertexBuffer(normalBuffer);

    ELVertexBufferPtr uvBuffer = ELVertexBuffer::alloc()->init(cubeTexCoords, sizeof(cubeTexCoords), sizeof(ELFloat) * 2, ELVertexBufferTypeStatic);
    ELVertexAttribute uvAttr;
    uvAttr.dataType = ELVertexAttributeDataTypeFloat;
    uvAttr.sizeInBytes = sizeof(ELFloat) * 2;
    uvAttr.offsetInBytes = 0;
    uvAttr.name = "v_texcoord";
    uvBuffer->addAttribute(uvAttr);
    sphereVertexBuffer->appendVertexBuffer(uvBuffer);

    ELVertexBufferPtr tangentBuffer = ELVertexBuffer::alloc()->init(cubeTangents, sizeof(cubeTangents), sizeof(ELFloat) * 3, ELVertexBufferTypeStatic);
    ELVertexAttribute tangentAttr;
    tangentAttr.dataType = ELVertexAttributeDataTypeFloat;
    tangentAttr.sizeInBytes = sizeof(ELFloat) * 3;
    tangentAttr.offsetInBytes = 0;
    tangentAttr.name = "v_tangent";
    tangentBuffer->addAttribute(tangentAttr);
    sphereVertexBuffer->appendVertexBuffer(tangentBuffer);

    ELVertexBufferPtr bitangentBuffer = ELVertexBuffer::alloc()->init(cubeBitangents, sizeof(cubeBitangents), sizeof(ELFloat) * 3, ELVertexBufferTypeStatic);
    ELVertexAttribute bitangentAttr;
    bitangentAttr.dataType = ELVertexAttributeDataTypeFloat;
    bitangentAttr.sizeInBytes = sizeof(ELFloat) * 3;
    bitangentAttr.offsetInBytes = 0;
    bitangentAttr.name = "v_bitangent";
    bitangentBuffer->addAttribute(bitangentAttr);
    sphereVertexBuffer->appendVertexBuffer(bitangentBuffer);
}
