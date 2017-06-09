#include "impl_OpenGL/ELGLAdapter.h"
#include <GLFW/glfw3.h>
#include "ELPlatform.h"
#include "TestScene.h"
#include <sstream>

std::vector<TestScene *> testScenes;
std::vector<std::string> sceneNames;

#define RegisterTestScene(Name, Desc) \
    sceneNames.push_back(Desc);\
    testScenes.push_back(new Name());

#include "Test Scenes/BasicFlowTests.h"
#include "Test Scenes/MultiBufferTests.h"
#include "Test Scenes/IndexBufferTests.h"

void registerScenes() {
    RegisterTestScene(BasicFlowTests, "基本渲染流程测试&渲染到纹理");
    RegisterTestScene(MultiBufferTests, "使用多Buffer渲染单个物体");
    RegisterTestScene(IndexBufferTests, "使用索引Buffer渲染单个物体");
}

int currentShowSceneIndex = 0;
double lastTime;
double elapsedTime;
void init(GLFWwindow *);
void gameLoop();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void syncTitle(GLFWwindow* window);

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
    init(window);

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

void init(GLFWwindow *window) {
    registerScenes();
    glfwSetKeyCallback(window, key_callback);
    lastTime = glfwGetTime();
    elapsedTime = 0;
    syncTitle(window);
}

void gameLoop() {
    if (testScenes.size() <= 0) {
        return;
    }
    double now = glfwGetTime();
    double deltaTime = now - lastTime;
    elapsedTime += deltaTime;
    lastTime = now;
    TestScene *scene = testScenes[currentShowSceneIndex];
    scene->update(deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        currentShowSceneIndex --;
        if (currentShowSceneIndex < 0) {
            currentShowSceneIndex = sceneNames.size() - 1;
        }
    } else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        currentShowSceneIndex ++;
        if (currentShowSceneIndex > sceneNames.size() - 1) {
            currentShowSceneIndex = 0;
        }
    }
    syncTitle(window);
}

void syncTitle(GLFWwindow* window) {
    if (sceneNames.size() <= 0) {
        return;
    }
    std::stringstream titleStream;
    titleStream << "（ " << currentShowSceneIndex + 1 << " / " << sceneNames.size() << " ） ";
    titleStream << sceneNames[currentShowSceneIndex];
    std::string copyOfStr = titleStream.str();
    glfwSetWindowTitle(window, copyOfStr.c_str());
}