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
void init() {
    ELRenderTargetPtr defaultRenderTarget = ELRenderTarget::defaultTarget();

    std::string vertexShader = "#version 330 core \n layout(location = 1) in vec4 position; in vec3 color; out vec3 fragColor; \n void main() { gl_Position = position; fragColor = color; }";
    std::string fragmentShader = "#version 330 core \n precision highp float; \n out vec3 outColor; in vec3 fragColor; uniform float u1; \n void main() { outColor = fragColor; }";
    pipline = ELRenderPipline::alloc()->init(vertexShader, fragmentShader);

    ELRenderPassConfig config = ELRenderPassConfig();
    config.clearColor = ELVector4Make(0.1, 0.1, 0.1, 1.0);
    config.loadAction = ELRenderPassLoadActionClear;
    mainRenderPass = ELRenderPass::alloc()->init(config, defaultRenderTarget);

    renderer = ELRenderer::alloc()->init(mainRenderPass, pipline);

    static GLfloat data[] = {
            0, 0.4, 0.0, 1.0, 1.0, 0.0, 0.0,
            -0.4, -0.4, 0.0, 1.0, 1.0, 1.0, 1.0,
            0.4, -0.4, 0.0, 1.0, 1.0, 0.0, 1.0,
    };
    triangleVertexBuffer = ELVertexBuffer::alloc()->init(data, sizeof(data), ELVertexBufferTypeStatic);
    ELVertexAttribute positionAttr;
    positionAttr.dataType = ELVertexAttributeDataTypeFloat;
    positionAttr.sizeInBytes = sizeof(GLfloat) * 4;
    positionAttr.offsetInBytes = 0;
    positionAttr.name = "position";
    triangleVertexBuffer->addAttribute(positionAttr);
    ELVertexAttribute colorAttr;
    colorAttr.dataType = ELVertexAttributeDataTypeFloat;
    colorAttr.sizeInBytes = sizeof(GLfloat) * 3;
    colorAttr.offsetInBytes = sizeof(GLfloat) * 4;
    colorAttr.name = "color";
    triangleVertexBuffer->addAttribute(colorAttr);
}

void gameLoop() {
    renderer->prepare();
//    renderer->drawPrimitives(ELPrimitivesTypeTriangle, triangleVertexBuffer);
    renderer->drawPrimitives(ELPrimitivesTypeLine, triangleVertexBuffer);
}