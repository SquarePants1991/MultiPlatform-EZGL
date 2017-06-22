//
// Created by wangyang on 2017/6/7.
//

#include "BasicFlowTests.h"

BasicFlowTests::BasicFlowTests() {
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();

    ELAssets::shared()->addSearchPath("/Users/wangyang/Documents/Codes/OnGit/MultiPlatform-EZGL/tests/platform/");
    ELAssets::shared()->addSearchPath("/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/tests/platform/");

    std::string vertexShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("vertex.glsl"));
    std::string fragmentShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("fragment.glsl"));

    pipline = ELRenderPipline::alloc()->init(vertexShader, fragmentShader);

    ELRenderPassConfig config = ELRenderPassConfigDefault();
    config.clearColor = ELVector4Make(0.1, 0.1, 0.1, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    mainRenderPass = ELRenderPass::alloc()->init(config, defaultRenderTarget);

    renderer = ELRenderer::alloc()->init(mainRenderPass, pipline);

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


    static ELFloat squareData[] = {
            -0.5, 0.5f, -0.5, 0, 0, 1, 0, 0,
            -0.5f, -0.5f, -0.5, 0, 0, 1, 0, 1,
            0.5f, -0.5f, -0.5, 0, 0, 1, 1, 1,
            0.5, -0.5f, -0.5, 0, 0, 1, 1, 1,
            0.5f, 0.5f, -0.5, 0, 0, 1, 1, 0,
            -0.5f, 0.5f, -0.5, 0, 0, 1, 0, 0
    };
    squareVertexBuffer = ELVertexBuffer::alloc()->init(squareData, sizeof(squareData), sizeof(ELFloat) * 8, ELVertexBufferTypeStatic);
    squareVertexBuffer->addAttribute(positionAttr);
    squareVertexBuffer->addAttribute(colorAttr);
    squareVertexBuffer->addAttribute(uvAttr);


    renderToTextureTarget = ELRenderTarget::alloc()->init(ELPixelFormatRGBA, ELVector2Make(1024, 1024), true, false, true, true, true);
    renderToTextureRenderPass = ELRenderPass::alloc()->init(config, renderToTextureTarget);
    renderToTextureRender = ELRenderer::alloc()->init(renderToTextureRenderPass, pipline);

    renderToDepthTextureTarget = ELRenderTarget::alloc()->init(ELPixelFormatDepth, ELVector2Make(1024, 1024), false, true, true, false, false);
    renderToDepthTextureRenderPass = ELRenderPass::alloc()->init(config, renderToDepthTextureTarget);
    renderToDepthTextureRender = ELRenderer::alloc()->init(renderToDepthTextureRenderPass, pipline);

    renderer->enableDepthTest();
    renderToTextureRender->disableDepthTest();
    renderToDepthTextureRender->enableDepthTest();
}

void BasicFlowTests::update(ELFloat deltaTime) {
    static float angle = 0.0;
    angle += 0.01;
    ELMatrix4 finalMatrix = ELMatrix4Identity;

    ELMatrix4 projection = ELMatrix4MakePerspective(90.0 * M_PI / 180.0, 640 / 480.0, 0.1, 1000);
    ELMatrix4 view = ELMatrix4MakeLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
    ELMatrix4 model = ELMatrix4MakeRotation(angle, 1, 1, 1);

    finalMatrix = ELMatrix4Multiply(view, model);
    finalMatrix = ELMatrix4Multiply(projection, finalMatrix);
    renderToTextureRender->prepare();
    renderToTextureRender->pipline->setUniform(finalMatrix, renderToTextureRender->pipline->getUniformLocation("transform"));
    renderToTextureRender->pipline->bindTexture(diffuseTexture, renderToTextureRender->pipline->getUniformLocation("diffuse"));
    renderToTextureRender->drawPrimitives(ELPrimitivesTypeTriangle, cubeVertexBuffer);

    renderToDepthTextureRender->prepare();
    renderToDepthTextureRender->pipline->setUniform(finalMatrix, renderToDepthTextureRender->pipline->getUniformLocation("transform"));
    renderToDepthTextureRender->pipline->bindTexture(diffuseTexture, renderToDepthTextureRender->pipline->getUniformLocation("diffuse"));
    renderToDepthTextureRender->drawPrimitives(ELPrimitivesTypeTriangle, cubeVertexBuffer);

    renderer->prepare();
    renderer->pipline->setUniform(finalMatrix, renderer->pipline->getUniformLocation("transform"));
    renderer->pipline->bindTexture(diffuseTexture, renderer->pipline->getUniformLocation("diffuse"));
    renderer->drawPrimitives(ELPrimitivesTypeTriangle, cubeVertexBuffer);

    renderer->pipline->clearState();
    renderer->pipline->bindTexture(renderToTextureTarget->bindTexture, renderer->pipline->getUniformLocation("diffuse"));
    projection = ELMatrix4MakeOrtho(-0.5, 3.5, -3.5, 0.5, 0, 100);
    renderer->pipline->setUniform(projection, renderer->pipline->getUniformLocation("transform"));
    renderer->drawPrimitives(ELPrimitivesTypeTriangle, squareVertexBuffer);

    renderer->pipline->clearState();
    renderer->pipline->bindTexture(renderToDepthTextureTarget->bindDepthTexture, renderer->pipline->getUniformLocation("diffuse"));
    projection = ELMatrix4MakeOrtho(-0.5, 3.5, -2.5, 1.5, 0, 100);
    renderer->pipline->setUniform(projection, renderer->pipline->getUniformLocation("transform"));
    renderer->drawPrimitives(ELPrimitivesTypeTriangle, squareVertexBuffer);
}