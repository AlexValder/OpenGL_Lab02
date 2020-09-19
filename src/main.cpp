#include <iostream>
#include <iomanip>

#include "opengl_adapter/Window.h"


int main()
{
    LAM::Vec2 td = {0, 0};

    std::cout << "x = " << td.x << " y = " << td.y << std::endl;
    std::cout << typeid(td.x).name() << std::endl;

    return 0;
}
