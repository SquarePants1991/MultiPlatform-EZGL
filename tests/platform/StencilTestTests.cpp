//
// Created by wang yang on 2017/6/19.
//

#include "StencilTestTests.h"

StencilTestTests::StencilTestTests(std::map<std::string, ELRenderPiplinePtr> piplines): TestScene(piplines) {
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();
    ELAssets::shared()->addSearchPath("/Users/wangyang/Documents/Codes/OnGit/MultiPlatform-EZGL/tests/platform/");
    ELAssets::shared()->addSearchPath("/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/tests/platform/");

    pipline = piplines.at("default");

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
            -0.5, 0.5f, 0.5, 0, 0, 1, 0, 0,
            -0.5f, -0.5f, 0.5, 0, 0, 1, 0, 1,
            0.5f, -0.5f, 0.5, 0, 0, 1, 1, 1,
            0.5, -0.5f, 0.5, 0, 0, 1, 1, 1,
            0.5f, 0.5f, 0.5, 0, 0, 1, 1, 0,
            -0.5f, 0.5f, 0.5, 0, 0, 1, 0, 0
    };
    squareVertexBuffer = ELVertexBuffer::alloc()->init(squareData, sizeof(squareData), sizeof(ELFloat) * 8, ELVertexBufferTypeStatic);
    squareVertexBuffer->addAttribute(positionAttr);
    squareVertexBuffer->addAttribute(colorAttr);
    squareVertexBuffer->addAttribute(uvAttr);

    renderer->enableDepthTest();
    renderer->enableStencilTest();
}

void StencilTestTests::update(ELFloat deltaTime) {
    static float angle = 0.0;
    angle += 0.01;
    ELMatrix4 finalMatrix = ELMatrix4Identity;

    ELMatrix4 projection = ELMatrix4MakePerspective(90.0 * M_PI / 180.0, 640 / 480.0, 0.1, 1000);
    ELMatrix4 view = ELMatrix4MakeLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
    ELMatrix4 model = ELMatrix4Identity;

    renderer->prepare();

    renderer->setStencilFunc(ELTestAlways, 1, 0xff);
    renderer->setStencilOperations(ELStencilOpKeep, ELStencilOpKeep, ELStencilOpReplace);
    renderer->setStencilMask(0xFF);
    
    model = ELMatrix4MakeTranslation(0, 0, -1.0);
    finalMatrix = ELMatrix4Multiply(view, model);
    finalMatrix = ELMatrix4Multiply(projection, finalMatrix);
    renderer->pipline->setUniform(finalMatrix, renderer->pipline->getUniformLocation("transform"));
    renderer->pipline->bindTexture(diffuseTexture, renderer->pipline->getUniformLocation("diffuse"));
    renderer->drawPrimitives(ELPrimitivesTypeTriangle, squareVertexBuffer);
    

    renderer->setStencilFunc(ELTestEqual, 1, 0xff);
    renderer->setStencilMask(0x00);
    
    model = ELMatrix4MakeRotation(angle, 1, 1, 1);
    finalMatrix = ELMatrix4Multiply(view, model);
    finalMatrix = ELMatrix4Multiply(projection, finalMatrix);
    renderer->pipline->setUniform(finalMatrix, renderer->pipline->getUniformLocation("transform"));
    renderer->pipline->bindTexture(diffuseTexture, renderer->pipline->getUniformLocation("diffuse"));
    renderer->drawPrimitives(ELPrimitivesTypeTriangle, cubeVertexBuffer);
    renderer->endRender();

}
