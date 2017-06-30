//
// Created by wang yang on 2017/6/13.
//

#include "BlendModeTests.h"


BlendModeTests::BlendModeTests(std::map<std::string, ELRenderPiplinePtr> piplines): TestScene(piplines) {
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();

    ELAssets::shared()->addSearchPath("/Users/wangyang/Documents/Codes/OnGit/MultiPlatform-EZGL/tests/platform/");
    ELAssets::shared()->addSearchPath("/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/tests/platform/");

    pipline = piplines.at("blend");

    ELRenderPassConfig config = ELRenderPassConfigDefault();
    config.clearColor = ELVector4Make(0.1, 0.1, 0.1, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    mainRenderPass = ELRenderPass::alloc()->init(config, defaultRenderTarget);

    renderer = ELRenderer::alloc()->init(mainRenderPass, pipline);

    std::string imagePath = ELAssets::shared()->findFile("texture.jpg");
    diffuseTexture = ELTexture::alloc()->init(imagePath);

    static ELFloat cubeData[] = {
            0.5, -0.5, 0.5f, 0.5773502691896258, -0.5773502691896258, 0.5773502691896258, 0, 0,   // VertexA
            0.5, -0.5f, -0.5f, 0.5773502691896258, -0.5773502691896258, -0.5773502691896258, 0, 1,   // VertexB
            0.5, 0.5f, -0.5f, 0.5773502691896258, 0.5773502691896258, -0.5773502691896258, 1, 1,   // VertexC
            0.5, 0.5f, 0.5f, 0.5773502691896258, 0.5773502691896258, 0.5773502691896258, 1, 0,   // VertexD
            -0.5, -0.5, 0.5f, -0.5773502691896258, -0.5773502691896258, 0.5773502691896258, 0, 0, // VertexE
            -0.5, -0.5f, -0.5f, -0.5773502691896258, -0.5773502691896258, -0.5773502691896258, 0, 1, // VertexF
            -0.5, 0.5f, -0.5f, -0.5773502691896258, 0.5773502691896258, -0.5773502691896258, 1, 1, // VertexG
            -0.5, 0.5f, 0.5f, -0.5773502691896258, 0.5773502691896258, 0.5773502691896258, 1, 0, // VertexH
    };

    static ELInt plane1[] = {
            6,      // VertexG
            5,      // VertexF
            1,      // VertexB
            1,      // VertexB
            2,      // VertexC
            6,      // VertexG
    };

    cubeVertexBuffer = ELVertexBuffer::alloc()->init(sizeof(ELFloat) * 8, ELVertexBufferTypeStatic);
    ELVertexAttribute positionAttr;
    positionAttr.dataType = ELVertexAttributeDataTypeFloat;
    positionAttr.sizeInBytes = sizeof(ELFloat) * 3;
    positionAttr.offsetInBytes = 0;
    positionAttr.name = "position";
    cubeVertexBuffer->addAttribute(positionAttr);
    ELVertexAttribute colorAttr;
    colorAttr.dataType = ELVertexAttributeDataTypeFloat;
    colorAttr.sizeInBytes = sizeof(ELFloat) * 3;
    colorAttr.offsetInBytes = sizeof(ELFloat) * 3;
    colorAttr.name = "color";
    cubeVertexBuffer->addAttribute(colorAttr);
    ELVertexAttribute uvAttr;
    uvAttr.dataType = ELVertexAttributeDataTypeFloat;
    uvAttr.sizeInBytes = sizeof(ELFloat) * 2;
    uvAttr.offsetInBytes = sizeof(ELFloat) * 6;
    uvAttr.name = "uv";
    cubeVertexBuffer->addAttribute(uvAttr);

    cubeVertexBuffer->append(cubeData, sizeof(cubeData));
    cubeVertexBuffer->flushBuffer();

    cubeVertexBuffer->enableIndex();
    cubeVertexBuffer->appendIndex(plane1, 6);
    cubeVertexBuffer->flushIndexBuffer();

    renderer->enableBlend();
    renderer->setBlendMode(ELBlendFactorSrcAlpha, ELBlendFactorOneMinusSrcAlpha);
    renderer->enableDepthTest();
}

void BlendModeTests::update(ELFloat deltaTime) {
    static float angle = 0.0;
    angle += 0.01;
    ELMatrix4 finalMatrix = ELMatrix4Identity;

    ELMatrix4 projection = ELMatrix4MakePerspective(90.0 * M_PI / 180.0, 640 / 480.0, 0.1, 1000);
    ELMatrix4 view = ELMatrix4MakeLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
    ELMatrix4 model = ELMatrix4MakeRotation(0, 1, 1, 1);

    finalMatrix = ELMatrix4Multiply(view, model);
    finalMatrix = ELMatrix4Multiply(projection, finalMatrix);

    renderer->prepare();
    model = ELMatrix4MakeTranslation(0.0, 0.2, -0.2);
    finalMatrix = ELMatrix4Identity;
    finalMatrix = ELMatrix4Multiply(view, model);
    finalMatrix = ELMatrix4Multiply(projection, finalMatrix);
    renderer->pipline->setUniform(finalMatrix, renderer->pipline->getUniformLocation("transform"));
    renderer->pipline->setUniform( ELVector4Make(1.0, 0.0, 1.0, 1.0), renderer->pipline->getUniformLocation("color"));
    renderer->drawPrimitives(ELPrimitivesTypeTriangle, cubeVertexBuffer);

    renderer->disableDepthWrite();
    model = ELMatrix4MakeTranslation(0.2, 0.1, 0.3);
    finalMatrix = ELMatrix4Identity;
    finalMatrix = ELMatrix4Multiply(view, model);
    finalMatrix = ELMatrix4Multiply(projection, finalMatrix);
    renderer->pipline->setUniform(finalMatrix, renderer->pipline->getUniformLocation("transform"));
    renderer->pipline->setUniform( ELVector4Make(1.0, 0.0, 0.0, 0.5), renderer->pipline->getUniformLocation("color"));
    renderer->drawPrimitives(ELPrimitivesTypeTriangle, cubeVertexBuffer);


    model = ELMatrix4MakeTranslation(0.25, 0.2, 0.2);
    finalMatrix = ELMatrix4Identity;
    finalMatrix = ELMatrix4Multiply(view, model);
    finalMatrix = ELMatrix4Multiply(projection, finalMatrix);
    renderer->pipline->setUniform(finalMatrix, renderer->pipline->getUniformLocation("transform"));
    renderer->pipline->setUniform(ELVector4Make(0.0, 0.7, 0.0, 0.5), renderer->pipline->getUniformLocation("color"));
    renderer->drawPrimitives(ELPrimitivesTypeTriangle, cubeVertexBuffer);
    renderer->enableDepthWrite();
    
    renderer->endRender();

    static float elapsedTime = 0.0;
    elapsedTime += deltaTime;
//    renderer->setBlendMode(ELBlendFactorOneMinusSrcAlpha, (ELBlendFactor)(((int)elapsedTime) % 9));
}
