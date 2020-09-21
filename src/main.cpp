#include <iostream>

#include "opengl_adapter/Application.h"
#include "opengl_adapter/Window.h"

template <class T>
std::ostream& operator<<(std::ostream& os, const LAM::Vec2<T>& td) {
    return os << "(" << td.x << ", " << td.y << ")";
}


int main() {

    LAM::Color colors[] = {LAM::Color::CYAN, LAM::Color::GREEN};
    LAM::Window::Point sizes[] = {{800, 600}, {600, 800}};

    LAM::AppInit();

    LAM::Window wind("Test", sizes[0]);
    wind.GrabContext();
    wind.SetSize(sizes[0]);

    uint counter{};

    wind.SetInput();

    do {
        LAM::SetClearColor(colors[0]);

        ++counter;
        wind.Render();
        if (counter == 100) {
            counter = 0;

            std::swap(sizes[0], sizes[1]);
            std::swap(colors[0], colors[1]);

            wind.SetSize(sizes[0]);
        }

    } while(!wind.AboutToClose());

    LAM::AppClose();

    return 0;
}
