#include "Renderer.h"

using namespace LAM;

void MainRenderer::InitGLFW(int major_version, int minor_version) {

    if (isGlfwInit()) return;

    assert(major_version >= 3 && minor_version >= 0);

    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);

    if (!(major_version < 4 && minor_version <= 2)) // 3.3+
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    setGlfwInit(true);
}

void MainRenderer::InitGLEW() {
    if (isGlewInit()) return;

    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    }

    setGlewInit(true);
    glEnable(GL_DEPTH_TEST);
}

void MainRenderer::SwapBuffers(Window& w) {
    assert(isGlfwInit() && isGlewInit());

    glfwSwapBuffers(w.handle);
}

void MainRenderer::SetClearColor(Color color) {
    assert(isGlfwInit() && isGlewInit());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color.R, color.G, color.B, color.A/255.f);
}
