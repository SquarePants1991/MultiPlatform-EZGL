#include "impl_OpenGL/ELGLAdapter.h"
#include <GLFW/glfw3.h>
#include <ELRenderPass.h>
#include <ELPlatform.h>
#include "ELPlatform.h"

void init();

void gameLoop();

int main(void) {
    GLFWwindow *window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
        return -1;
    printf("%s", (char *) glGetString(GL_SHADING_LANGUAGE_VERSION));

    ELGLAdapter::defaultAdapter()->setup(window);
    init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        gameLoop();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

ELRenderPiplinePtr pipline;
ELRenderPassPtr mainRenderPass;
ELRendererPtr renderer;
ELVertexBufferPtr cubeVertexBuffer;
ELVertexBufferPtr squareVertexBuffer;
ELTexturePtr diffuseTexture;

ELRenderTargetPtr renderToTextureTarget;
ELRenderPassPtr renderToTextureRenderPass;
ELRendererPtr renderToTextureRender;

ELRenderTargetPtr renderToDepthTextureTarget;
ELRenderPassPtr renderToDepthTextureRenderPass;
ELRendererPtr renderToDepthTextureRender;

void init() {
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();

    ELAssets::shared()->addSearchPath("/Users/wangyang/Documents/Projects/On Git/EZGLKit_M/tests/platform/");
    ELAssets::shared()->addSearchPath("/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/tests/platform/");

    std::string vertexShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("vertex.glsl"));
    std::string fragmentShader = ELFileUtil::stringContentOfShader(ELAssets::shared()->findFile("fragment.glsl"));

    pipline = ELRenderPipline::alloc()->init(vertexShader, fragmentShader);

    ELRenderPassConfig config = ELRenderPassConfig();
    config.clearColor = ELVector4Make(0.1, 0.1, 0.1, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    mainRenderPass = ELRenderPass::alloc()->init(config, defaultRenderTarget);

    renderer = ELRenderer::alloc()->init(mainRenderPass, pipline);

    std::string imagePath = ELAssets::shared()->findFile("texture.jpg");
    diffuseTexture = ELTexture::alloc()->init(imagePath);
    static GLfloat data[] = {
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

    cubeVertexBuffer = ELVertexBuffer::alloc()->init(data, sizeof(data), ELVertexBufferTypeStatic);
    ELVertexAttribute positionAttr;
    positionAttr.dataType = ELVertexAttributeDataTypeFloat;
    positionAttr.sizeInBytes = sizeof(GLfloat) * 3;
    positionAttr.offsetInBytes = 0;
    positionAttr.name = "position";
    cubeVertexBuffer->addAttribute(positionAttr);
    ELVertexAttribute colorAttr;
    colorAttr.dataType = ELVertexAttributeDataTypeFloat;
    colorAttr.sizeInBytes = sizeof(GLfloat) * 3;
    colorAttr.offsetInBytes = sizeof(GLfloat) * 3;
    colorAttr.name = "color";
    cubeVertexBuffer->addAttribute(colorAttr);
    ELVertexAttribute uvAttr;
    uvAttr.dataType = ELVertexAttributeDataTypeFloat;
    uvAttr.sizeInBytes = sizeof(GLfloat) * 2;
    uvAttr.offsetInBytes = sizeof(GLfloat) * 6;
    uvAttr.name = "uv";
    cubeVertexBuffer->addAttribute(uvAttr);


    static GLfloat squareData[] = {
            -0.5, 0.5f, -0.5, 0, 0, 1, 0, 0,
            -0.5f, -0.5f, -0.5, 0, 0, 1, 0, 1,
            0.5f, -0.5f, -0.5, 0, 0, 1, 1, 1,
            0.5, -0.5f, -0.5, 0, 0, 1, 1, 1,
            0.5f, 0.5f, -0.5, 0, 0, 1, 1, 0,
            -0.5f, 0.5f, -0.5, 0, 0, 1, 0, 0
    };
    squareVertexBuffer = ELVertexBuffer::alloc()->init(squareData, sizeof(squareData), ELVertexBufferTypeStatic);
    squareVertexBuffer->addAttribute(positionAttr);
    squareVertexBuffer->addAttribute(colorAttr);
    squareVertexBuffer->addAttribute(uvAttr);


    renderToTextureTarget = ELRenderTarget::alloc()->init(ELPixelFormatRGBA, ELVector2Make(1024, 1024), true, false, true, true, true);
    renderToTextureRenderPass = ELRenderPass::alloc()->init(config, renderToTextureTarget);
    renderToTextureRender = ELRenderer::alloc()->init(renderToTextureRenderPass, pipline);

    renderToDepthTextureTarget = ELRenderTarget::alloc()->init(ELPixelFormatDepth, ELVector2Make(1024, 1024), false, true, true, false, false);
    renderToDepthTextureRenderPass = ELRenderPass::alloc()->init(config, renderToDepthTextureTarget);
    renderToDepthTextureRender = ELRenderer::alloc()->init(renderToDepthTextureRenderPass, pipline);
}

void gameLoop() {
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
    renderToTextureRender->pipline->bindTexture(diffuseTexture, renderToTextureRender->pipline->getUniformLocation("diffuse"), 0);
    renderToTextureRender->drawPrimitives(ELPrimitivesTypeTriangle, cubeVertexBuffer);

    renderToDepthTextureRender->prepare();
    renderToDepthTextureRender->pipline->setUniform(finalMatrix, renderToDepthTextureRender->pipline->getUniformLocation("transform"));
    renderToDepthTextureRender->pipline->bindTexture(diffuseTexture, renderToDepthTextureRender->pipline->getUniformLocation("diffuse"), 0);
    renderToDepthTextureRender->drawPrimitives(ELPrimitivesTypeTriangle, cubeVertexBuffer);

    renderer->prepare();
    renderer->pipline->setUniform(finalMatrix, renderer->pipline->getUniformLocation("transform"));
    renderer->pipline->bindTexture(diffuseTexture, renderer->pipline->getUniformLocation("diffuse"), 0);
    renderer->drawPrimitives(ELPrimitivesTypeTriangle, cubeVertexBuffer);

    renderer->pipline->bindTexture(renderToTextureTarget->bindTexture, renderer->pipline->getUniformLocation("diffuse"), 0);
    projection = ELMatrix4MakeOrtho(-0.5, 3.5, -3.5, 0.5, 0, 100);
    renderer->pipline->setUniform(projection, renderer->pipline->getUniformLocation("transform"));
    renderer->drawPrimitives(ELPrimitivesTypeTriangle, squareVertexBuffer);

    renderer->pipline->bindTexture(renderToDepthTextureTarget->bindDepthTexture, renderer->pipline->getUniformLocation("diffuse"), 0);
    projection = ELMatrix4MakeOrtho(-0.5, 3.5, -2.5, 1.5, 0, 100);
    renderer->pipline->setUniform(projection, renderer->pipline->getUniformLocation("transform"));
    renderer->drawPrimitives(ELPrimitivesTypeTriangle, squareVertexBuffer);
}