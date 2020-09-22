#include <iostream>
#include <array>

#include "opengl_adapter/Application.h"
#include "opengl_adapter/Window.h"

template <class T>
std::ostream& operator<<(std::ostream& os, const LAM::Vec2<T>& td) {
    return os << "(" << td.x << ", " << td.y << ")";
}

bool AreAllOpen(std::array<LAM::Window, 3>& vec) {
    bool res = true;
    for (auto& win : vec) {
        res = res && !win.AboutToClose();
    }
    return res;
}


int main() {

    LAM::Color colors[] = {LAM::Color::CYAN, LAM::Color::GREEN, LAM::Color::PURPLE};
    LAM::Window::Point sizes[] = {{800, 600}, {600, 800}, {500, 500}};

    LAM::AppInit();

    std::array<LAM::Window, 3> windows = {
        LAM::Window("Test1", sizes[0]),
        LAM::Window("Test2", sizes[1]),
        LAM::Window("Test3", sizes[2])
    };

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

            std::swap(sizes[0], sizes[1]);
            std::swap(sizes[1], sizes[2]);
            std::swap(colors[0], colors[1]);
            std::swap(colors[1], colors[2]);

            for (size_t i = 0; i < windows.size(); ++i) {
                windows[i].SetSize(sizes[i]);
            }
        }

    } while(AreAllOpen(windows));

    LAM::AppClose();

    return 0;
}
