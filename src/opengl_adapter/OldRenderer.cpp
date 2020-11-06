#include "Renderer.h"

using namespace LAM;

void OldRenderer::InitGLFW(int major_version, int minor_version) {

    if (isGlfwInit()) return;

    assert(major_version >= 0 && minor_version >= 0);
    assert(major_version <= 2);

    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);

    setGlfwInit(true);
}

void OldRenderer::InitGLEW() {
    if (isGlewInit()) return;

    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    }

    setGlewInit(true);
    glEnable(GL_DEPTH_TEST);
}

void OldRenderer::SwapBuffers(Window& w) {
    assert(isGlfwInit() && isGlewInit());

    glfwSwapBuffers(w.handle);
}

void OldRenderer::SetClearColor(Color color) {
    assert(isGlfwInit() && isGlewInit());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color.R, color.G, color.B, color.A/255.f);
}
