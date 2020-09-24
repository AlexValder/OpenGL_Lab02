#include <iostream>
#include <array>

// how many windows will be opened?
constexpr size_t num = 1;

#include "opengl_adapter/Renderer.h"
#include "opengl_adapter/Window.h"

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


int main(int argc, const char** argv) {

    LAM::Color colors[] = { LAM::Color::CYAN, LAM::Color::GREEN, LAM::Color::PURPLE, LAM::Color::OLIVE };
    LAM::Window::Point sizes[] = {{800, 600}, {800, 700}, {800, 800}, {800, 700}};

    LAM::RendererBase* renderer = new LAM::MainRenderer;
    renderer->Init();

    std::cout << "Loban A., PA-18-2" << std::endl;
    std::string custom_title = (argc >= 2) ? argv[1] : "Test";
    LAM::Window::Point begin_size = (argc >= 4) ?
                sizes[0] = LAM::Window::Point(atoi(argv[2]), atoi(argv[3]))
              : sizes[0];

    std::array<LAM::Window, num> windows = {
        LAM::Window(custom_title, begin_size)/*,
        LAM::Window("Test2", sizes[1]),
        LAM::Window("Test3", sizes[2])*/
    };

    assert(0 <= num && num <= sizeof(colors));
    assert(0 <= num && num <= sizeof(sizes));
    assert(num == windows.size());

    for (size_t i = 0; i < windows.size(); ++i) {
        windows[i].SetSize(sizes[i]);
        windows[i].SetInput();
    }


    uint counter{};

    do {
        ++counter;

        for (size_t i = 0; i < windows.size(); ++i) {
            renderer->MakeContextCurrent(windows[i]);
            renderer->SetClearColor(colors[i]);
            renderer->RenderWindow(windows[i]);
        }

        if (counter == 100) {
            counter = 0;

            move_forward(colors, sizeof(colors)/sizeof(colors[0]));
            move_forward(sizes, sizeof(sizes)/sizeof(sizes[0]));

            for (size_t i = 0; i < windows.size(); ++i) {
                windows[i].SetSize(sizes[i]);
            }
        }

    } while(AreAllOpen(windows));

    delete renderer;

    return 0;
}
