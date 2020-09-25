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

int main() {

    std::cout << "Loban A., PA-18-2" << std::endl;

    LAM::Color colors[] = { LAM::Color::BLUE, LAM::Color::GREEN, LAM::Color::PURPLE, LAM::Color::GRAY };

    LAM::RendererBase* renderer = new LAM::MainRenderer;
    renderer->InitGLFW(2, 1);

    std::array<LAM::Window, num> windows = {
        LAM::Window("Test1", {800, 800}),
        LAM::Window("Test2", {500, 500}),
        LAM::Window("Test3", {800, 800})
    };

    assert(0 < num && num <= sizeof(colors)/sizeof(colors[0]));
    assert(num == windows.size());

    renderer->MakeContextCurrent(windows[1]);
    renderer->InitGLEW();

    LAM::Cube::Init();

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
