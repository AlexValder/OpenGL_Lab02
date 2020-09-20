#include <iostream>

#include "opengl_adapter/Application.h"
#include "opengl_adapter/Window.h"

template <class T>
std::ostream& operator<<(std::ostream& os, const LAM::Vec2<T>& td) {
    return os << "(" << td.x << ", " << td.y << ")";
}

int main() {

    LAM::AppInit();

    LAM::Window wind("Test", {600, 800});
    wind.GrabContext();

    uint counter{};

    wind.SetInput();

    auto cur_color = LAM::Color::CYAN;

    std::cout << sizeof(cur_color) << std::endl;

    do {
        LAM::SetClearColor(cur_color);

        ++counter;
        wind.Render();
        if (counter == 100) {
            wind.SetSize({600, 480});
            cur_color = LAM::Color::GREEN;
            std::cout << wind.GetPos() << std::endl
                      << wind.GetSize() << std::endl;
        }

    } while(wind.AboutToClose());

    LAM::AppClose();

    return 0;
}
