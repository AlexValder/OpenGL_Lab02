#include <iostream>
#include <array>

#include "opengl_adapter/Renderer.h"
#include "opengl_adapter/Window.h"
#include "opengl_adapter/Shader.h"

#define DRAW_CUBE_INSTEAD_OF_A_TRIANGLE 1
#define USE_OLD_RENDERER 0

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

// for changing color and size.
template <typename T>
void move_forward(T vec[], size_t size) {
    for (size_t i = 2; i <= size; ++i) {
        std::swap(vec[size - i], vec[size - 1]);
    }
}

// how many windows will be opened?
constexpr size_t num = 1;

int main(int argc, const char** argv) {

    std::cout << "Loban A., PA-18-2" << std::endl;
    try {

        LAM::Color colors[] = { LAM::Color::BLACK, LAM::Color(0, 0, 50, 255), LAM::Color(0, 50, 0, 255), LAM::Color(50, 0, 0, 255) };
        LAM::Window::Point pos[] = { {0, 0}, {300, 300}, {500, 500} };
    #if USE_OLD_RENDERER
        LAM::RendererBase* renderer = new LAM::OldRenderer;
        renderer->InitGLFW(2, 1);
    #else
        LAM::RendererBase* renderer = new LAM::MainRenderer;
        renderer->InitGLFW(3, 1);
    #endif

        assert(0 < num && num <= sizeof(colors)/sizeof(colors[0]));
        assert(num <= sizeof(pos)/sizeof(pos[0]));

        std::array<LAM::Window, num> windows = {
            LAM::Window(argc >= 2 ? argv[1] : "Test1", {700, 700})/*,
            LAM::Window(argc >= 3 ? argv[2] : "Test2", {475, 475}),
            LAM::Window(argc >= 4 ? argv[3] : "Test3", {200, 200})*/
        };

        assert(num == windows.size());

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

            glMatrixMode(GL_MODELVIEW); //set the matrix to model view mode

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
            LAM::Cube::Init();
        }

        LAM::Shader shader("resources/vertex_shader.shader", "resources/fragment_shader.shader");

        std::cout << "SHADER.ID = " << shader.ID() << std::endl;

        auto action = [](){
            const static GLuint VAO = LAM::Cube::VAO;
            const static GLenum TYPE = LAM::Cube::TYPE;
            const static size_t size = LAM::Cube::vertices.size();
            glBindVertexArray(VAO);
            glEnableVertexAttribArray(0);

            glMatrixMode(GL_MODELVIEW); //set the matrix to model view mode

            glPushMatrix(); // push the matrix
            double angle = glfwGetTime() * 50.0f;
            glRotatef(angle, 0.5, 1.5, 0.5); //apply transformation

            glLineWidth(5);
            glDrawArrays(TYPE, 0, size);

            glPopMatrix();

            glDisableVertexAttribArray(0);
        };
#else // Triangle with "modern" renderer
        auto action = [](){

        };
#endif

        uint counter{};

        while(AreAllOpen(windows)) {
            ++counter;

            for (size_t i = 0; i < windows.size(); ++i) {
                renderer->SetClearColor(colors[i]);
                renderer->MakeContextCurrent(windows[i]);

                renderer->Render(action);

                renderer->SwapBuffers(windows[i]);
                renderer->PollEvents();
            }

            if (counter == 100) {
                move_forward(colors, sizeof(colors)/sizeof(colors[0]));
                counter = 0;
            }

        }
#if DRAW_CUBE_INSTEAD_OF_A_TRIANGLE
        for (auto& win : windows) {
            renderer->MakeContextCurrent(win);
            LAM::Cube::Deinit();
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
