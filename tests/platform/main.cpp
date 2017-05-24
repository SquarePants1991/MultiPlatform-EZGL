#include "impl_OpenGL/ELGLAdapter.h"
#include <GLFW/glfw3.h>
#include <ELRenderPass.h>
#include "ELPlatform.h"

void init();
void gameLoop();

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

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
void init() {
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();

    std::string vertexShader = "void main() { gl_Position = vec4(1.0, 0.0, 0.0, 1.0); }";
    std::string fragmentShader = "void main() { gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); }";
    pipline = ELRenderPipline::alloc()->init(vertexShader, fragmentShader);

    ELRenderPassConfig config = ELRenderPassConfig();
    config.clearColor = ELVector4Make(1.0, 0.0, 0.5, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    mainRenderPass = ELRenderPass::alloc()->init(config, defaultRenderTarget);

    renderer = ELRenderer::alloc()->init(mainRenderPass, pipline);
}

void gameLoop() {
    renderer->prepare();
    renderer->drawPrimitives(ELPrimitivesTypePoint, ELVertexBuffer::alloc());
}