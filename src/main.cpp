#include <iostream>
#include <array>

#include "opengl_adapter/Renderer.h"
#include "opengl_adapter/Window.h"
#include "opengl_adapter/Shader.h"
#include "opengl_adapter/KeyController.h"

#define DRAW_CUBE_INSTEAD_OF_A_TRIANGLE 1
#define USE_OLD_RENDERER 0
// how many windows will be opened?
#define WIN_COUNT 1

#if DRAW_CUBE_INSTEAD_OF_A_TRIANGLE
#include "objects_to_draw/Cube.h"
#else
#include "objects_to_draw/Squares.h"
#endif

// to print a Vec2 as (x, y).
template <class T>
std::ostream& operator<<(std::ostream& os, const LAM::Vec2<T>& td) {
    return os << "(" << td.x << ", " << td.y << ")";
}

// are all windows open?
template<typename T>
bool AreAllOpen(const T& vec) {
    bool res = true;
    for (auto& win : vec) {
        res = res && !win.AboutToClose();
    }
    return res;
}

void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode);
void processInput(GLFWwindow *, LAM::Camera&, float);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

static LAM::Camera camera(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 1.0f, 10.f);
static float deltaTime{};
static bool oneColor = false;
static LAM::Color cubeColor = LAM::Color::WHITE;
static LAM::Color bgColor = LAM::Color::BLACK;

int main(int argc, const char** argv) {

    static_assert((USE_OLD_RENDERER) ^ (!USE_OLD_RENDERER && (WIN_COUNT == 1)), "You should only use one window with OpenGL 3.0+");
    static_assert(WIN_COUNT >= 1 && WIN_COUNT <= 3, "You can only create from 1 to 3 windows at one time.");
    srand(time(0));

    LAM::KeyController::AddAction(LAM::Keys::A, [](float delta){
        camera.ProcessKeyboard(LAM::CameraMovement::LEFT, delta);
    });

    LAM::KeyController::AddAction(LAM::Keys::D, [](float delta){
        camera.ProcessKeyboard(LAM::CameraMovement::RIGHT, delta);
    });

    LAM::KeyController::AddAction(LAM::Keys::W, [](float delta){
        camera.ProcessKeyboard(LAM::CameraMovement::FORWARD, delta);
    });

    LAM::KeyController::AddAction(LAM::Keys::S, [](float delta){
        camera.ProcessKeyboard(LAM::CameraMovement::BACKWARD, delta);
    });

    LAM::KeyController::AddAction(LAM::Keys::Escape, [](){
        glfwTerminate();
        exit(0);
    });

    LAM::KeyController::AddAction(LAM::Keys::Q, []() {
       if (oneColor) {
            cubeColor = LAM::Color::RandomColor();
            LAM::DebugPrint("Cube color: %s", cubeColor.toString().c_str());
       }
    });

    LAM::KeyController::AddAction(LAM::Keys::C, []() {
        oneColor = !oneColor;
        LAM::DebugPrint("Manual cube color switching toggled.");
    });

    LAM::KeyController::AddAction(LAM::Keys::E, []() {
        bgColor = LAM::Color::RandomColor(0, 80);
        LAM::DebugPrint("Background color: %s", bgColor.toString().c_str());
    });

    std::cout << "Loban A., PA-18-2" << std::endl;
    try {

    #if USE_OLD_RENDERER
        LAM::RendererBase* renderer = new LAM::OldRenderer;
        renderer->InitGLFW(2, 1);
    #else
        LAM::RendererBase* renderer = new LAM::MainRenderer;
        renderer->InitGLFW(3, 3);
    #endif

        std::array<LAM::Window, WIN_COUNT> windows = {
            LAM::Window(argc >= 2 ? argv[1] : "Test1", {700, 700})
    #if WIN_COUNT > 1
            ,
            LAM::Window(argc >= 3 ? argv[2] : "Test2", {475, 475})
    #endif
    #if WIN_COUNT > 2
            ,
            LAM::Window(argc >= 4 ? argv[3] : "Test3", {200, 200})
    #endif
        };

        renderer->MakeContextCurrent(windows[0]);
        renderer->InitGLEW();

        std::cout << "We're running on: " << glGetString(GL_VERSION) << std::endl;

#if DRAW_CUBE_INSTEAD_OF_A_TRIANGLE && USE_OLD_RENDERER // Cube with old renderer

        for (auto& win : windows) {
            renderer->MakeContextCurrent(win);
            LAM::Cube::Init();
        }

        auto action = [](){
            const static GLuint VAO = LAM::Cube::VAO;
            const static GLenum TYPE = LAM::Cube::TYPE;
            const static size_t size = LAM::Cube::vertices.size();
            glBindVertexArray(VAO);
            glEnableVertexAttribArray(0);

            glMatrixMode(GL_PROJECTION); //set the matrix to model view mode

            glPushMatrix(); // push the matrix
            double angle = glfwGetTime() * 50.0f;
            glRotatef(angle, 0.5, 1.5, 0.5); //apply transformation

            glLineWidth(5);
            glDrawArrays(TYPE, 0, size);

            glPopMatrix();

            glDisableVertexAttribArray(0);
        };

#elif USE_OLD_RENDERER // Triangle with old renderer

        auto action = [](){
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
        };

#elif DRAW_CUBE_INSTEAD_OF_A_TRIANGLE // Cube with "modern" renderer

        for (auto& win : windows) {
            renderer->MakeContextCurrent(win);
            glfwSetKeyCallback(win.GetHandle(), keyCallback);
            glfwSetCursorPosCallback(win.GetHandle(), mouse_callback);
            glfwSetScrollCallback(win.GetHandle(), scroll_callback);
            LAM::Cube::Init();
        }

        LAM::Camera cam(glm::vec3(0.0f));

        auto action = [&](){

            static LAM::Shader shader("resources/cube_vertex_shader.vert", "resources/cube_fragment_shader.frag");
            const static GLuint VAO = LAM::Cube::VAO;
            const static GLenum TYPE = LAM::Cube::TYPE;
            const static size_t size = LAM::Cube::vertices.size();

            const static auto mat4e = glm::mat4(1.f);

            shader.Use();

            shader.setMat4("model", glm::rotate(mat4e, (float)glfwGetTime() * glm::radians(66.6f), glm::vec3(4.04f, 4.2f, 1.3f)));
            shader.setMat4("view", mat4e);//cam.GetViewMatrix());
            shader.setMat4("projection", mat4e);
            if (!oneColor) {
                shader.setVec4("ourColor",
                               abs(cos(glfwGetTime() * 2.f)),
                               abs(sin(glfwGetTime() * 2.f)),
                               abs(sin(glfwGetTime() * 1.3f)),
                               abs(cos(glfwGetTime() * 0.5f)));
            }
            else {
                shader.setVec4("ourColor", cubeColor);
            }

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindVertexArray(VAO);
            glDrawArrays(TYPE, 0, size);
        };

#else // Triangle with "modern" renderer

        for (auto& win : windows) {
            renderer->MakeContextCurrent(win);
            LAM::Triangle::Init();
        }

        auto action = [&](){
            static LAM::Shader shader("resources/triangle_vertex_shader.vert", "resources/triangle_fragment_shader.frag");
            const static GLuint VAO = LAM::Triangle::VAO;
            const static GLenum TYPE = LAM::Triangle::TYPE;

            const static auto mat4e = glm::mat4(1.f);

            shader.Use();

            shader.setMat4("model", glm::rotate(mat4e, (float)glfwGetTime() * glm::radians(66.6f), glm::vec3(4.04f, 4.2f, 1.3f)));
            shader.setMat4("view", mat4e);
            shader.setMat4("projection", mat4e);

            glBindVertexArray(VAO);
            glDrawArrays(TYPE, 0, 3);

        };

#endif

        float lastFrame{};

        while(AreAllOpen(windows)) {
            for (size_t i = 0; i < windows.size(); ++i) {
                renderer->SetClearColor(bgColor);
                renderer->MakeContextCurrent(windows[i]);

                float currentFrame = glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;

                renderer->Render(action);

                renderer->SwapBuffers(windows[i]);
                renderer->PollEvents();
            }
        }
#if DRAW_CUBE_INSTEAD_OF_A_TRIANGLE
        for (auto& win : windows) {
            renderer->MakeContextCurrent(win);
            LAM::Cube::Deinit();
        }
#elif !USE_OLD_RENDERER && !DRAW_CUBE_INSTEAD_OF_A_TRIANGLE
        for (auto& win : windows) {
            renderer->MakeContextCurrent(win);
            LAM::Triangle::Deinit();
        }
#endif
        delete renderer;
    }
    catch (std::exception& ex) {

        std::cout << ex.what() << std::endl;
        return -1;
    }
    return 0;
}

void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode) {
    if (action == GLFW_RELEASE) {
        LAM::KeyController::PerformAction(static_cast<LAM::Keys>(key), deltaTime);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static float lastX{}, lastY{};
    static bool firstMouse = true;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}
