#include <iostream>
#include <array>

#include "opengl_adapter/Renderer.h"
#include "opengl_adapter/Window.h"

#include "objects_to_draw/Cube.h"

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
constexpr size_t num = 3;

int main(int argc, const char** argv) {

    std::cout << "Loban A., PA-18-2" << std::endl;

    LAM::Color colors[] = { LAM::Color::BLUE, LAM::Color::GREEN, LAM::Color::PURPLE, LAM::Color::BLACK };
    LAM::Window::Point pos[] = { {0, 0}, {300, 300}, {500, 500} };

    LAM::RendererBase* renderer = new LAM::MainRenderer;
    renderer->InitGLFW(2, 1);

    assert(0 < num && num <= sizeof(colors)/sizeof(colors[0]));
    assert(num <= sizeof(pos)/sizeof(pos[0]));

    std::array<LAM::Window, num> windows = {
        LAM::Window(argc >= 2 ? argv[1] : "Test1", {700, 700}, false),
        LAM::Window(argc >= 3 ? argv[2] : "Test2", {475, 475}, false),
        LAM::Window(argc >= 4 ? argv[3] : "Test3", {200, 200}, false)
    };

    for (size_t i = 0; i < windows.size(); ++i) {
        windows[i].SetPos(pos[i]);
    }

    assert(num == windows.size());

    renderer->MakeContextCurrent(windows[0]);

    renderer->InitGLEW();

    for (auto& wind : windows) {
		renderer->MakeContextCurrent(wind);
        LAM::Cube::Init();
    }

    uint counter{};

    while(AreAllOpen(windows)) {
        ++counter;

        for (size_t i = 0; i < windows.size(); ++i) {
            renderer->SetClearColor(colors[i]);
            renderer->MakeContextCurrent(windows[i]);
            renderer->RenderVBO(LAM::Cube::VAO, LAM::Cube::TYPE, LAM::Cube::vertices.size());
            renderer->SwapBuffers(windows[i]);
            renderer->PollEvents();
        }

        if (counter == 100) {
            move_forward(colors, sizeof(colors)/sizeof(colors[0]));
            counter = 0;
        }

    }

    LAM::Cube::Deinit();

    delete renderer;
    return 0;
}
