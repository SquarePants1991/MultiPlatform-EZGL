//
// Created by wang yang on 2017/7/4.
//

#include "BaseRendererTests.h"

BaseRendererTests::BaseRendererTests(std::map<std::string, ELRenderPiplinePtr> piplines) {
    ELRenderPassConfig config = ELRenderPassConfigDefault();
    config.clearColor = ELVector4Make(0.1, 0.1, 0.1, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();
    baseRenderer = ELBaseRenderer::alloc()->init(config, defaultRenderTarget);


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
}

void BaseRendererTests::update(ELFloat deltaTime) {
    static float angle = 0.0;
    angle += 0.01;

    ELMatrix4 projection = ELMatrix4MakePerspective(90.0 * M_PI / 180.0, 640 / 480.0, 0.1, 1000);
    ELMatrix4 view = ELMatrix4MakeLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
    ELMatrix4 model = ELMatrix4MakeRotation(angle, 1, 1, 1);

    baseRenderer->beginDraw();

    baseRenderer->setVertexBuffer(cubeVertexBuffer);
    baseRenderer->setDiffuseMap(diffuseTexture);
    baseRenderer->setModelMatrix(model);
    baseRenderer->setViewMatrix(view);
    baseRenderer->setProjectionMatrix(projection);
    baseRenderer->draw(ELPrimitivesTypeTriangle);

    baseRenderer->commitDraw();
}