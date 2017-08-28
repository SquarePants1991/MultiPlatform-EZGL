//
// Created by wang yang on 2017/8/18.
//

#include <renderer/ELLambertPhongRenderer.h>
#include "LambertPhongShadowTests.h"
#include "sphere.h"


LambertPhongShadowTests::LambertPhongShadowTests(std::map<std::string, ELRenderPiplinePtr> piplines) {
    ELRenderPassConfig config = ELRenderPassConfigDefault();
    config.clearColor = ELVector4Make(0.1, 0.1, 0.1, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();
    lambertPhongRenderer = ELLambertPhongRenderer::alloc()->init(config, defaultRenderTarget);

    setupShadowMapRenderer();
    std::string imagePath = ELAssets::shared()->findFile("texture.jpg");
    diffuseTexture = ELTexture::alloc()->init(imagePath);
    static ELFloat data[] = {
            // X轴0.5处的平面
            0.5, -0.5, 0.5f, 1, 0, 0, 0, 0,
            0.5, -0.5f, -0.5f, 1, 0, 0, 0, 1,
            0.5, 0.5f, -0.5f, 1, 0, 0, 1, 1,
            0.5, 0.5, -0.5f, 1, 0, 0, 1, 1,
            0.5, 0.5f, 0.5f, 1, 0, 0, 1, 0,
            0.5, -0.5f, 0.5f, 1, 0, 0, 0, 0,
            // X轴-0.5处的平面
            -0.5, -0.5, 0.5f, -1, 0, 0, 0, 0,
            -0.5, -0.5f, -0.5f, -1, 0, 0, 0, 1,
            -0.5, 0.5f, -0.5f, -1, 0, 0, 1, 1,
            -0.5, 0.5, -0.5f, -1, 0, 0, 1, 1,
            -0.5, 0.5f, 0.5f, -1, 0, 0, 1, 0,
            -0.5, -0.5f, 0.5f, -1, 0, 0, 0, 0,

            -0.5, 0.5, 0.5f, 0, 1, 0, 0, 0,
            -0.5f, 0.5, -0.5f, 0, 1, 0, 0, 1,
            0.5f, 0.5, -0.5f, 0, 1, 0, 1, 1,
            0.5, 0.5, -0.5f, 0, 1, 0, 1, 1,
            0.5f, 0.5, 0.5f, 0, 1, 0, 1, 0,
            -0.5f, 0.5, 0.5f, 0, 1, 0, 0, 0,
            -0.5, -0.5, 0.5f, 0, -1, 0, 0, 0,
            -0.5f, -0.5, -0.5f, 0, -1, 0, 0, 1,
            0.5f, -0.5, -0.5f, 0, -1, 0, 1, 1,
            0.5, -0.5, -0.5f, 0, -1, 0, 1, 1,
            0.5f, -0.5, 0.5f, 0, -1, 0, 1, 0,
            -0.5f, -0.5, 0.5f, 0, -1, 0, 0, 0,

            -0.5, 0.5f, 0.5, 0, 0, 1, 0, 0,
            -0.5f, -0.5f, 0.5, 0, 0, 1, 0, 1,
            0.5f, -0.5f, 0.5, 0, 0, 1, 1, 1,
            0.5, -0.5f, 0.5, 0, 0, 1, 1, 1,
            0.5f, 0.5f, 0.5, 0, 0, 1, 1, 0,
            -0.5f, 0.5f, 0.5, 0, 0, 1, 0, 0,
            -0.5, 0.5f, -0.5, 0, 0, -1, 0, 0,
            -0.5f, -0.5f, -0.5, 0, 0, -1, 0, 1,
            0.5f, -0.5f, -0.5, 0, 0, -1, 1, 1,
            0.5, -0.5f, -0.5, 0, 0, -1, 1, 1,
            0.5f, 0.5f, -0.5, 0, 0, -1, 1, 0,
            -0.5f, 0.5f, -0.5, 0, 0, -1, 0, 0,
    };

    cubeVertexBuffer = ELVertexBuffer::alloc()->init(data, sizeof(data), sizeof(ELFloat) * 8, ELVertexBufferTypeStatic);
    ELVertexAttribute positionAttr;
    positionAttr.dataType = ELVertexAttributeDataTypeFloat;
    positionAttr.sizeInBytes = sizeof(ELFloat) * 3;
    positionAttr.offsetInBytes = 0;
    positionAttr.name = "v_position";
    cubeVertexBuffer->addAttribute(positionAttr);
    ELVertexAttribute colorAttr;
    colorAttr.dataType = ELVertexAttributeDataTypeFloat;
    colorAttr.sizeInBytes = sizeof(ELFloat) * 3;
    colorAttr.offsetInBytes = sizeof(ELFloat) * 3;
    colorAttr.name = "v_normal";
    cubeVertexBuffer->addAttribute(colorAttr);
    ELVertexAttribute uvAttr;
    uvAttr.dataType = ELVertexAttributeDataTypeFloat;
    uvAttr.sizeInBytes = sizeof(ELFloat) * 2;
    uvAttr.offsetInBytes = sizeof(ELFloat) * 6;
    uvAttr.name = "v_texcoord";
    cubeVertexBuffer->addAttribute(uvAttr);

    // create sphere
    sphereVertexBuffer = ELCompositionVertexBuffer::alloc()->init();

    ELVertexBufferPtr vertexBuffer = ELVertexBuffer::alloc()->init(sphereVerts, sizeof(sphereVerts), sizeof(ELFloat) * 3, ELVertexBufferTypeStatic);
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
    uvAttr.dataType = ELVertexAttributeDataTypeFloat;
    uvAttr.sizeInBytes = sizeof(ELFloat) * 2;
    uvAttr.offsetInBytes = 0;
    uvAttr.name = "v_texcoord";
    uvBuffer->addAttribute(uvAttr);
    sphereVertexBuffer->appendVertexBuffer(uvBuffer);

    lightWithShadow.lightType = ELLightTypeDirect;
    lightWithShadow.color = ELVector3Make(1.0, 1.0, 1.0);
    lightWithShadow.indensity = 1;
    lightWithShadow.pose = ELVector3Make(1,-1,1);
}

void LambertPhongShadowTests::update(ELFloat deltaTime) {
    static float elapsedTime = 0.0;
    elapsedTime += deltaTime;
    lightWithShadow.pose = ELVector3Make(sin(elapsedTime),-1,cos(elapsedTime));

    renderToShadowMap();

    ELMatrix4 projection = ELMatrix4MakePerspective(90.0 * M_PI / 180.0, 640 / 480.0, 0.1, 1000);
    ELMatrix4 view = ELMatrix4MakeLookAt(1.0, 1.1, -1.0, 0, 0, 0, 0, 1, 0);
    ELMatrix4 model = ELMatrix4MakeRotation(0, 1, 1, 1);

    bool canInvert;
    ELMatrix4 normalMatrix = ELMatrix4Invert(model, &canInvert);
    normalMatrix = ELMatrix4Transpose(normalMatrix);

    ELLightInfo light[1];
    light[0] = lightWithShadow;


    ELLambertPhongMaterial materialSphere;
    materialSphere.diffuseColor = ELVector3Make(0.0, 0.0, 1.0);
    materialSphere.useDiffuseMap = false;
    materialSphere.ambientColor = ELVector3Make(0.2, 0.2, 0.2);
    materialSphere.specularColor = ELVector3Make(1.0, 1.0, 1.0);
    materialSphere.specularIndensity = 1.0;
    materialSphere.smoothness = 300;

    ELLambertPhongMaterial materialCube;
    materialCube.diffuseColor = ELVector3Make(0.6, 0.1, 0.2);
    materialCube.useDiffuseMap = false;
    materialCube.ambientColor = ELVector3Make(0.2, 0.2, 0.2);
    materialCube.specularColor = ELVector3Make(1.0, 1.0, 1.0);
    materialCube.specularIndensity = 1.0;
    materialCube.smoothness = 10;

    ELMatrix4 lightProjection =  ELMatrix4MakeOrtho(-10, 10, -10, 10, -30, 30);
    ELMatrix4 lightView = ELMatrix4MakeLookAt(-lightWithShadow.pose.x, -lightWithShadow.pose.y, -lightWithShadow.pose.z, 0, 0, 0, 0, 1, 0);
    ELMatrix4 lightPV = ELMatrix4Multiply(lightProjection, lightView);


    lambertPhongRenderer->beginDraw();


    // draw sphere
    model = ELMatrix4MakeTranslation(0, 0.5, 0);
    lambertPhongRenderer->setNormalMapEnable(false);
    lambertPhongRenderer->enableShadow(true);
    lambertPhongRenderer->setShadowMap(shadowMapRenderTarget->bindDepthTexture);
    lambertPhongRenderer->setLightProjectionMatrix(lightPV);
    lambertPhongRenderer->setVertexBuffer(sphereVertexBuffer);
    lambertPhongRenderer->setLights(light, sizeof(light) / sizeof(ELLightInfo));
    lambertPhongRenderer->setCameraPosition(ELVector3Make(0, 0, 1.1));
    lambertPhongRenderer->setMaterial(materialSphere);
    lambertPhongRenderer->setDiffuseMap(diffuseTexture);
    lambertPhongRenderer->setModelMatrix(model);
    lambertPhongRenderer->setNormalMatrix(normalMatrix);
    lambertPhongRenderer->setViewMatrix(view);
    lambertPhongRenderer->setProjectionMatrix(projection);
    lambertPhongRenderer->draw(ELPrimitivesTypeTriangle);


    // draw cube
    model = ELMatrix4MakeScale(4, 0.2, 4);
    model = ELMatrix4Multiply(ELMatrix4MakeTranslation(0, -0.1, 0), model);
    lambertPhongRenderer->setNormalMapEnable(false);
    lambertPhongRenderer->enableShadow(true);
    lambertPhongRenderer->setShadowMap(shadowMapRenderTarget->bindDepthTexture);
    lambertPhongRenderer->setLightProjectionMatrix(lightPV);
    lambertPhongRenderer->setVertexBuffer(cubeVertexBuffer);
    lambertPhongRenderer->setLights(light, sizeof(light) / sizeof(ELLightInfo));
    lambertPhongRenderer->setCameraPosition(ELVector3Make(0, 0, 1.1));
    lambertPhongRenderer->setMaterial(materialCube);
    lambertPhongRenderer->setDiffuseMap(diffuseTexture);
    lambertPhongRenderer->setModelMatrix(model);
    lambertPhongRenderer->setNormalMatrix(normalMatrix);
    lambertPhongRenderer->setViewMatrix(view);
    lambertPhongRenderer->setProjectionMatrix(projection);
    lambertPhongRenderer->draw(ELPrimitivesTypeTriangle);

    lambertPhongRenderer->commitDraw();
}

void LambertPhongShadowTests::setupShadowMapRenderer() {
    ELRenderPassConfig config = ELRenderPassConfigDefault();
    config.clearColor = ELVector4Make(0.1, 0.1, 0.1, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    shadowMapRenderTarget = ELRenderTarget::alloc()->init(ELPixelFormatDepth, ELVector2Make(1024, 1024), false, true, true, false, false);
    shadowMapRenderer = ELBaseRenderer::alloc()->init(config, shadowMapRenderTarget);
}

void LambertPhongShadowTests::renderToShadowMap() {
//    ELMatrix4 projection = ELMatrix4MakePerspective(90.0 * M_PI / 180.0, 640 / 480.0, 0.1, 1000);
    ELMatrix4 projection =  ELMatrix4MakeOrtho(-10, 10, -10, 10, -30, 30);
    ELMatrix4 view = ELMatrix4MakeLookAt(-lightWithShadow.pose.x, -lightWithShadow.pose.y, -lightWithShadow.pose.z, 0, 0, 0, 0, 1, 0);
    ELMatrix4 model = ELMatrix4MakeRotation(0, 1, 1, 1);

    bool canInvert;
    ELMatrix4 normalMatrix = ELMatrix4Invert(model, &canInvert);
    normalMatrix = ELMatrix4Transpose(normalMatrix);


    shadowMapRenderer->beginDraw();


    // draw sphere
    model = ELMatrix4MakeTranslation(0, 0.5, 0);
    shadowMapRenderer->setNormalMapEnable(false);
    shadowMapRenderer->setVertexBuffer(sphereVertexBuffer);
    shadowMapRenderer->setDiffuseMap(diffuseTexture);
    shadowMapRenderer->setModelMatrix(model);
    shadowMapRenderer->setNormalMatrix(normalMatrix);
    shadowMapRenderer->setViewMatrix(view);
    shadowMapRenderer->setProjectionMatrix(projection);
    shadowMapRenderer->draw(ELPrimitivesTypeTriangle);


    // draw cube
    model = ELMatrix4MakeScale(4, 0.2, 4);
    model = ELMatrix4Multiply(ELMatrix4MakeTranslation(0, -0.1, 0), model);
    shadowMapRenderer->setNormalMapEnable(false);
    shadowMapRenderer->setVertexBuffer(cubeVertexBuffer);
    shadowMapRenderer->setDiffuseMap(diffuseTexture);
    shadowMapRenderer->setModelMatrix(model);
    shadowMapRenderer->setNormalMatrix(normalMatrix);
    shadowMapRenderer->setViewMatrix(view);
    shadowMapRenderer->setProjectionMatrix(projection);
    shadowMapRenderer->draw(ELPrimitivesTypeTriangle);

    shadowMapRenderer->commitDraw();
}