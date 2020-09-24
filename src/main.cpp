#include <iostream>
#include <array>

constexpr size_t num = 1;

#include "opengl_adapter/Application.h"
#include "opengl_adapter/Window.h"

template <class T>
std::ostream& operator<<(std::ostream& os, const LAM::Vec2<T>& td) {
    return os << "(" << td.x << ", " << td.y << ")";
}

template<typename T>
bool AreAllOpen(const T& vec) {
    bool res = true;
    for (auto& win : vec) {
        res = res && !win.AboutToClose();
    }
    return res;
}

template <typename T>
void move_forward(T vec[], size_t size) {
    for (size_t i = 2; i <= size; ++i) {
        std::swap(vec[size - i], vec[size - 1]);
    }
}


int main() {

    LAM::Color colors[] = {LAM::Color::CYAN, LAM::Color::GREEN, LAM::Color::PURPLE, LAM::Color::GRAY};
    LAM::Window::Point sizes[] = {{800, 600}, {800, 700}, {800, 800}, {800, 700}};

    LAM::AppInit();

    std::array<LAM::Window, num> windows = {
        LAM::Window("Test1", sizes[0])/*,
        LAM::Window("Test2", sizes[1]),
        LAM::Window("Test3", sizes[2])*/
    };

    assert(num <= sizeof(colors));
    assert(num <= sizeof(sizes));
    assert(num == windows.size());

    for (size_t i = 0; i < windows.size(); ++i) {
        windows[i].SetSize(sizes[i]);
        windows[i].SetInput();
    }


    uint counter{};

    do {
        ++counter;

        for (size_t i = 0; i < windows.size(); ++i) {
            windows[i].GrabContext();
            LAM::SetClearColor(colors[i]);
            windows[i].Render();
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

    LAM::AppClose();

    return 0;
}
