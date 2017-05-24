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
    glewInit();
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
void init() {
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();

    std::string vertexShader = "#version 330 core \n in vec4 position; \n void main() { gl_Position = position; }";
    std::string fragmentShader = "#version 330 core \n out vec4 outColor; \n void main() { outColor = vec4(1.0, 0.0, 0.0, 1.0); }";
    pipline = ELRenderPipline::alloc()->init(vertexShader, fragmentShader);

    ELRenderPassConfig config = ELRenderPassConfig();
    config.clearColor = ELVector4Make(1.0, 0.0, 0.5, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    mainRenderPass = ELRenderPass::alloc()->init(config, defaultRenderTarget);

    renderer = ELRenderer::alloc()->init(mainRenderPass, pipline);

    triangleVertexBuffer = ELVertexBuffer::alloc();
    ELVertexAttribute positionAttr;
    positionAttr.dataType = ELVertexAttributeDataTypeFloat;
    positionAttr.sizeInBytes = sizeof(GLfloat) * 3;
    positionAttr.offsetInBytes = 0;
    positionAttr.name = "position";
    triangleVertexBuffer->addAttribute(positionAttr);

    static ELFloat data[] = {
            0, 0.5, 0.0,
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0
    };
    triangleVertexBuffer->append(data, sizeof(ELFloat) * 9);
}

void gameLoop() {
    renderer->prepare();
    renderer->drawPrimitives(ELPrimitivesTypeTriangle, triangleVertexBuffer);
}