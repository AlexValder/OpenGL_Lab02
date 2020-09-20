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
    wind.Open();

    uint counter{};

    wind.SetInput();

    do {
        LAM::SetClearColor(LAM::Color::CYAN);

        ++counter;
        wind.Render();
        if (counter == 100) {
            wind.SetSize({600, 480});
            std::cout << wind.GetPos() << std::endl
                      << wind.GetSize() << std::endl;
        }

    } while(wind.AboutToClose());

    LAM::AppClose();

    return 0;
}
