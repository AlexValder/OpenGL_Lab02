#ifndef WINDOW_H
#define WINDOW_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shared.h"

namespace LAM {

    class Window {
    public:
        Window();
        void Open() const;
        void Close();

        void SetTitle(const std::string& title);
        std::string GetTitle() const;


    private:
        GLFWwindow* window;
    };
}

#endif // WINDOW_H
