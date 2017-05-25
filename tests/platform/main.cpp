#include "impl_OpenGL/ELGLAdapter.h"
#include <GLFW/glfw3.h>
#include <ELRenderPass.h>
#include <ELPlatform.h>
#include "ELPlatform.h"

void init();
void gameLoop();

int main(void)
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental=true;
    if (glewInit() != GLEW_OK)
        return -1;
    printf("%s", (char *)glGetString ( GL_SHADING_LANGUAGE_VERSION ));

    ELGLAdapter::defaultAdapter()->setup(window);
    init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
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
ELVertexBufferPtr triangleVertexBuffer;
ELTexturePtr diffuseTexture;
void init() {
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();

    ELAssets::shared()->addSearchPath("/Users/wangyang/Documents/Projects/On Git/EZGLKit_M/tests/platform/");

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
            0.5,  -0.5,    0.5f, 1,  0,  0, 0, 0,
            0.5,  -0.5f,  -0.5f, 1,  0,  0, 0, 1,
            0.5,  0.5f,   -0.5f, 1,  0,  0, 1, 1,
            0.5,  0.5,    -0.5f, 1,  0,  0, 1, 1,
            0.5,  0.5f,    0.5f, 1,  0,  0, 1, 0,
            0.5,  -0.5f,   0.5f, 1,  0,  0, 0, 0,
            // X轴-0.5处的平面
            -0.5,  -0.5,    0.5f, -1,  0,  0, 0, 0,
            -0.5,  -0.5f,  -0.5f, -1,  0,  0, 0, 1,
            -0.5,  0.5f,   -0.5f, -1,  0,  0, 1, 1,
            -0.5,  0.5,    -0.5f, -1,  0,  0, 1, 1,
            -0.5,  0.5f,    0.5f, -1,  0,  0, 1, 0,
            -0.5,  -0.5f,   0.5f, -1,  0,  0, 0, 0,

            -0.5,  0.5,  0.5f, 0,  1,  0, 0, 0,
            -0.5f, 0.5, -0.5f, 0,  1,  0, 0, 1,
            0.5f, 0.5,  -0.5f, 0,  1,  0, 1, 1,
            0.5,  0.5,  -0.5f, 0,  1,  0, 1, 1,
            0.5f, 0.5,   0.5f, 0,  1,  0, 1, 0,
            -0.5f, 0.5,  0.5f, 0,  1,  0, 0, 0,
            -0.5, -0.5,   0.5f, 0,  -1,  0, 0, 0,
            -0.5f, -0.5, -0.5f, 0,  -1,  0, 0, 1,
            0.5f, -0.5,  -0.5f, 0,  -1,  0, 1, 1,
            0.5,  -0.5,  -0.5f, 0,  -1,  0, 1, 1,
            0.5f, -0.5,   0.5f, 0,  -1,  0, 1, 0,
            -0.5f, -0.5,  0.5f, 0,  -1,  0, 0, 0,

            -0.5,   0.5f,  0.5,   0,  0,  1, 0, 0,
            -0.5f,  -0.5f,  0.5,  0,  0,  1, 0, 1,
            0.5f,   -0.5f,  0.5,  0,  0,  1, 1, 1,
            0.5,    -0.5f, 0.5,   0,  0,  1, 1, 1,
            0.5f,  0.5f,  0.5,    0,  0,  1, 1, 0,
            -0.5f,   0.5f,  0.5,  0,  0,  1, 0, 0,
            -0.5,   0.5f,  -0.5,   0,  0,  -1, 0, 0,
            -0.5f,  -0.5f,  -0.5,  0,  0,  -1, 0, 1,
            0.5f,   -0.5f,  -0.5,  0,  0,  -1, 1, 1,
            0.5,    -0.5f, -0.5,   0,  0,  -1, 1, 1,
            0.5f,  0.5f,  -0.5,    0,  0,  -1, 1, 0,
            -0.5f,   0.5f,  -0.5,  0,  0,  -1, 0, 0,
    };

    triangleVertexBuffer = ELVertexBuffer::alloc()->init(data, sizeof(data), ELVertexBufferTypeStatic);
    ELVertexAttribute positionAttr;
    positionAttr.dataType = ELVertexAttributeDataTypeFloat;
    positionAttr.sizeInBytes = sizeof(GLfloat) * 3;
    positionAttr.offsetInBytes = 0;
    positionAttr.name = "position";
    triangleVertexBuffer->addAttribute(positionAttr);
    ELVertexAttribute colorAttr;
    colorAttr.dataType = ELVertexAttributeDataTypeFloat;
    colorAttr.sizeInBytes = sizeof(GLfloat) * 3;
    colorAttr.offsetInBytes = sizeof(GLfloat) * 3;
    colorAttr.name = "color";
    triangleVertexBuffer->addAttribute(colorAttr);
    ELVertexAttribute uvAttr;
    uvAttr.dataType = ELVertexAttributeDataTypeFloat;
    uvAttr.sizeInBytes = sizeof(GLfloat) * 2;
    uvAttr.offsetInBytes = sizeof(GLfloat) * 6;
    uvAttr.name = "uv";
    triangleVertexBuffer->addAttribute(uvAttr);
}

void gameLoop() {
    static float angle = 0.0;
    angle += 0.01;
    ELMatrix4 finalMatrix = ELMatrix4Identity;

    ELMatrix4 projection = ELMatrix4MakePerspective(90.0 * M_PI / 180.0, 640 / 480.0, 0.1, 1000);
    ELMatrix4 view = ELMatrix4MakeLookAt(0,0,2,0,0,0,0,1,0);
    ELMatrix4 model = ELMatrix4MakeRotation(angle, 1, 1, 1);

    finalMatrix = ELMatrix4Multiply(view, model);
    finalMatrix = ELMatrix4Multiply(projection, finalMatrix);
    renderer->prepare();
    renderer->pipline->setUniform(finalMatrix, renderer->pipline->getUniformLocation("transform"));
    renderer->pipline->bindTexture(diffuseTexture, renderer->pipline->getUniformLocation("diffuse"), 0);
    renderer->drawPrimitives(ELPrimitivesTypeTriangle, triangleVertexBuffer);
}