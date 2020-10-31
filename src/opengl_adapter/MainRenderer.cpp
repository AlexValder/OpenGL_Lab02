#include "Renderer.h"

using namespace LAM;

void MainRenderer::InitGLFW(int major_version, int minor_version) {

    if (isGlfwInit()) return;

    assert(major_version >= 3);

    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
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

//void MainRenderer::RenderTriangles(GLfloat*, GLfloat*) {
//    assert(isGlfwInit() && isGlewInit());

//    glClear(GL_COLOR_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//    glLoadIdentity();

//    glRotatef(static_cast<float>(glfwGetTime()) * 50.f, 1.f, 1.f, 1.f);

//    glBegin(GL_TRIANGLES);
//    glColor3f(1.f, 0.f, 0.f);
//    glVertex3f(-.6f, -.4f, 0.f);
//    glColor3f(0.f, 1.f, 0.f);
//    glVertex3f(.6f, -.4f, 0.f);
//    glColor3f(0.f, 0.f, 1.f);
//    glVertex3f(0.f, .6f, 0.f);
//    glEnd();

//}

//void MainRenderer::RenderVBO(GLuint VAO, GLenum TYPE, int size) {
//    assert(isGlfwInit() && isGlewInit());

//    glBindVertexArray(VAO);
//    glEnableVertexAttribArray(0);

//    glEnable(GL_DEPTH_TEST);

//    glMatrixMode(GL_MODELVIEW); //set the matrix to model view mode


//    glPushMatrix(); // push the matrix
//    double angle = glfwGetTime() * 50.0f;
//    glRotatef(angle, 0.5, 1.5, 0.5); //apply transformation

//    glLineWidth(5);
//    glDrawArrays(TYPE, 0, size);

//    glPopMatrix();

//    glDisableVertexAttribArray(0);
//}

void MainRenderer::SetClearColor(Color color) {
    assert(isGlfwInit() && isGlewInit());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color.R, color.G, color.B, color.A/255.f);
}
