#include <iostream>
#include <thread>

#include "opengl_adapter/Window.h"


int main()
{
    glfwInit();

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x Сглаживание
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Мы хотим использовать OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    LAM::Vec2<uint16_t> td = {600, 800};

    try {
        LAM::Window wind("Test", td);
        wind.Open();

        glewExperimental=true;
        glewInit();
        wind.SetInput();

        do {
            glClearColor(0, 255, 255, 0.0f);

            glClear(GL_COLOR_BUFFER_BIT);
            wind.Render();

        } while(wind.AboutToClose());
    }
    catch(std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        glfwTerminate();
    }

    return 0;
}
