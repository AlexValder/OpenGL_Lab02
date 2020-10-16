#include "Renderer.h"

using namespace LAM;

/// RendererBase

bool RendererBase::_isGlfwInit = false;
bool RendererBase::_isGlewInit = false;

bool RendererBase::isGlfwInit() const noexcept {
    return _isGlfwInit;
}

bool RendererBase::isGlewInit() const noexcept {
    return _isGlewInit;
}

void RendererBase::setGlfwInit(bool val) noexcept {
    _isGlfwInit = val;
}

void RendererBase::setGlewInit(bool val) noexcept {
    _isGlewInit = val;
}

/// OldRenderer

void OldRenderer::InitGLFW(int major_version, int minor_version) {

    if (isGlfwInit()) return;

    assert(major_version >= 0 && minor_version >= 0);
    assert(major_version <= 2 || (major_version == 2 && minor_version <= 1));

    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
}

void OldRenderer::InitGLEW() {
    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    }
}

void OldRenderer::SwapBuffers(Window& w) {
    glfwSwapBuffers(w.handle);
}

void OldRenderer::RenderTriangles(GLfloat*, GLfloat*) {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();

    glRotatef(static_cast<float>(glfwGetTime()) * 50.f, 1.f, 1.f, 1.f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-.6f, -.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(.6f, -.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, .6f, 0.f);
    glEnd();

}

void OldRenderer::RenderVBO(GLuint VAO, GLenum TYPE, int size) {
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW); //set the matrix to model view mode


    glPushMatrix(); // push the matrix
    double angle = glfwGetTime() * 50.0f;
    glRotatef(angle, 0.5, 1.5, 0.5); //apply transformation

    glLineWidth(5);
    glDrawArrays(TYPE, 0, size);

    glPopMatrix();

    glDisableVertexAttribArray(0);
}

void OldRenderer::SetClearColor(Color color) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color.R, color.G, color.B, color.A/255.f);
}

OldRenderer::~OldRenderer() {
    glfwTerminate();
}
